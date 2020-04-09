#include "InputPoint.h"
#include "Exception.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cctype>
#include <cmath>

using namespace std;


InputPoint::InputPoint(int index, const InputFile& file, const InputParams& params, double& tFloor, double& tCeil, double& moy_errij2)
{
    // ---------------------------------------------------------
    //  Arguments
    // ---------------------------------------------------------
    vector<string> values = file.mPointsStr[index];
    double latReduc = file.mLatReduc;
    double lngReduc = file.mLngReduc;

    double EctYij;
    double rYij;
    double Pij;
    string ch_contrainte_strati;

    // ---------------------------------------------------------
    // On commence par lire les variables sous forme de strings
    // ---------------------------------------------------------
    string strIdent = values[0];
    string strCode = values[1]; // ch_code_select

    string strLat = values[2]; // ch_lati
    string strLng = values[3]; // ch_longi

    string strInc = values[4]; // ch_Iij
    string strDec = values[5]; // ch_Dij
    string strK = values[6]; // ch_Kij
    string strND = values[7]; // ch_rij
    string strWID = values[8]; // ch_WIDij
    string strF = values[9]; // ch_Fij
    string strStdF = values[10]; // ch_EctFij
    string strNF = values[11]; // ch_rFij
    string strWF = values[12]; // ch_WFij

    string strDatingMeth = upper(values[13]); // ch_methode_datation
    string strParam1 = values[14]; // ch_param1
    string strParam2 = values[15]; // ch_param2
    string strT1 = values[16]; // ch_tdij1
    string strT2 = values[17]; // ch_tdij2
    string strTm = values[18]; // ch_tdijm

    string strStratiForId = upper(values[19]); // ch_contrainte_strati_ID
    string strStratiForF = upper(values[20]); // ch_contrainte_strati_F

    // ---------------------------------------------------------
    // On convertit les valeurs numériques
    // ---------------------------------------------------------
    double lat = this->parseDouble(strLat);
    double lng = this->parseDouble(strLng);
    double inc = this->parseDouble(strInc);
    double dec = this->parseDouble(strDec);
    double k = this->parseDouble(strK);
    double nd = this->parseDouble(strND);
    double wid = this->parseDouble(strWID);
    double f = this->parseDouble(strF);
    double stdF = this->parseDouble(strStdF);
    double nF = this->parseDouble(strNF);
    double wF = this->parseDouble(strWF);

    double param1 = this->parseDouble(strParam1);
    double param2 = this->parseDouble(strParam2);

    // Encadrement en année exacte en restant au format réel
    double t1 = floorf(this->parseDouble(strT1));
    double t2 = ceilf(this->parseDouble(strT2));

    double tm = this->parseDouble(strTm);

    // ---------------------------------------------------------
    //  Vérification des temps
    // ---------------------------------------------------------
    if (t1 > t2){
        throw Exception("Problème au point " + strIdent + " : inversion de date");
    }

    // ----------------------------------------------------------------------------------------------------------
    //  On ne retient que les points compris (totalement ou partiellement) entre tmin et tmax,
    // ----------------------------------------------------------------------------------------------------------
    if((t2 <= params.mTmin) || (t1 >= params.mTmax))
    {
        throw Exception("Problème au point " + strIdent + " : pas dans la plage de dates");
    }

    // ----------------------------------------------------------------------------------------------------------
    // Sélection éventuelle par zone géographique
    // ----------------------------------------------------------------------------------------------------------
    if(params.mSelectOuv)
    {
        double latReducRadian = latReduc * radian;
        double lngReducRadian = lngReduc * radian;
        double latRadian = lat * radian;
        double lngRadian = lng * radian;
        double ouv = (cos(latRadian) * cos(latReducRadian) * cos(lngRadian - lngReducRadian)) + (sin(latRadian) * sin(latReducRadian));
        ouv = acos(ouv) * degre;
        if(ouv >= params.mOuvMax)
        {
            throw Exception("Problème au point " + strIdent + " : ouverture supérieure à celle requise");
        }
    }

    // ----------------------------------------------------------------------------------------------------------
    //  Traitements univariés
    // ----------------------------------------------------------------------------------------------------------
    if(params.mProcessType == PROCESS_TYPE_UNIVARIE)
    {
        // ----------------------------------------------------------------------------------------------------------
        //  Mode inclinaison
        // ----------------------------------------------------------------------------------------------------------
        if(params.mVariableType == VAR_TYPE_INCLINAISON)
        {
            if ((strInc == "") || (strInc == "*") || (wid == 0) || (k == 0) || (nd <= 1)){
                throw Exception("Point invalide " + strIdent + " : données incorrecte pour le mode inclinaison");
            }

            if(params.mUseCorrLat){
                inc = inc + 0.5 * 3. * (sqrt(cos(inc * radian)) + 1) * (latReduc - lat);
            }

            // Yij:=Fij;  Cette opération est effectuée avant l'appel à "Do_cravate" dans Unit "traitement_spline"
            // pour tous les cas de type_Var_CMT

            // Qu'il s'agisse de struct. en place ou de matériaux déplacés, on rentre toujours K dans le fichier csv
            // K est alors calculé comme: K = (1/sqr(SI))*rad où SI est l'écart-type (au sens de la dispersion) sur l'inclinaison I
            EctYij = (1. / sqrt(k)) * degre;
            rYij = nd;
            Pij = wid;
            ch_contrainte_strati = strStratiForId;
        }

        // ----------------------------------------------------------------------------------------------------------
        //  Mode déclinaison
        // ----------------------------------------------------------------------------------------------------------
        else if(params.mVariableType == VAR_TYPE_DECLINAISON)
        {
            if ((strInc == "") || (strInc == "*") || (strDec == "") || (strDec == "*") || (wid == 0) || (k == 0) || (nd <= 1)){
                throw Exception("Point invalide " + strIdent + " : données incorrecte pour le mode déclinaison");
            }

            // On ramène les déclinations entre -180 et +180
            // les déclinaisons sont positives vers l'est et négatives vers l'ouest
            if(dec > 180.){
                dec = dec - 360.;
            }

            // Pas de correction de latitude sur déclinaison seule

            EctYij = (1. / (sqrt(k) * cos(inc * radian))) * degre;
            rYij = nd;
            Pij = wid;
            ch_contrainte_strati = strStratiForId;
        }

        // ----------------------------------------------------------------------------------------------------------
        //  Mode intensité
        // ----------------------------------------------------------------------------------------------------------
        else if(params.mVariableType == VAR_TYPE_INTENSITE)
        {
            if ((strF == "") || (strF == "*") || (stdF == 0) || (nF <= 0) || (wF == 1)){
                throw Exception("Point invalide " + strIdent + " : données incorrecte pour le mode intensité");
            }

            if(params.mUseCorrLat){
                f = f + sqrt( (3. * sqrt(sin(latReduc * radian)) + 1.) / (3. * sqrt(sin(lat * radian)) + 1.) );
            }

            EctYij = stdF;
            rYij = nF;
            Pij = wF;
            ch_contrainte_strati = strStratiForF;
        }

        // ----------------------------------------------------------------------------------------------------------
        //  Mode profondeur
        // ----------------------------------------------------------------------------------------------------------
        else if(params.mVariableType == VAR_TYPE_PROFONDEUR)
        {
            if ((strF == "") || (strF == "*") || (stdF == 0) || (nF <= 0) || (wF == 0)){
                throw Exception("Point invalide " + strIdent + " : données incorrecte pour le mode profondeur");
            }

            // les profondeurs traitées doivent être négatives
            f = -f; 

            EctYij = stdF;
            rYij = nF;
            Pij = wF;
            ch_contrainte_strati = strStratiForF;
        }
    }

    // ----------------------------------------------------------------------------------------------------------
    //  Mode sphérique
    // ----------------------------------------------------------------------------------------------------------
    else if(params.mProcessType == PROCESS_TYPE_SPHERIQUE)
    {
        if ((strInc == "") || (strInc == "*") || (strDec == "") || (strDec == "*") || (wid == 0) || (k == 0) || (nd <= 1)){
            throw Exception("Point invalide " + strIdent + " : données incorrecte pour le mode sphérique");
        }

        if(params.mUseCorrLat)
        {
            // Correction VGP exacte: Westphal, p.117 et Merill McElhinny, p.80
            // Les resultats ont ete verifies avec le logiciel PMAGTOOL a Sofia en 2001
            double latReducRadian = latReduc * radian;
            double lngReducRadian = lngReduc * radian;
            double latRadian = lat * radian;
            double lngRadian = lng * radian;

            // Calcul de la distance p du pôle
            double pol = (M_PI / 2) - atan(tan(inc * radian) / 2);
            double lap = asin(sin(latRadian) * cos(pol) + cos(latRadian) * sin(pol) * cos(dec * radian));
            double beta = asin(sin(pol) * sin(dec * radian) / cos(lap));
            double lgp = lngRadian + M_PI - beta;
            if(cos(pol) >= (sin(latRadian) * sin(lap))){
                lgp = lngRadian + beta;
            }

            // Calcul de Iij et Dij corrigés
            pol = acos(sin(latReducRadian) * sin(lap) + cos(latReducRadian) * cos(lap) * cos(lgp - lngReducRadian));
            inc = atan(2 * tan((M_PI / 2) - pol)) * degre;
            dec = asin(sin(lgp - lngReducRadian) * cos(lap) / sin(pol)) * degre;
        }

        // l'erreur, en degrés, est considérée identique sur X et Y dans le cas sphérique
        EctYij = (1. / sqrt(k)) * degre;
        rYij = nd;
        Pij = wid;
        ch_contrainte_strati = strStratiForId;
    }
    // ----------------------------------------------------------------------------------------------------------
    //  Mode vectoriel
    // ----------------------------------------------------------------------------------------------------------
    else if(params.mProcessType == PROCESS_TYPE_VECTORIEL)
    {
        // la routine S sphérique n'est pas opérationnelle: on passe par 'V' en posant F = Constante
        bool isFConstant = true;

        if ((strInc == "") || (strInc == "*") || (strDec == "") || (strDec == "*") || (wid == 0) || (k == 0) || (nd <= 1)){
            throw Exception("Point invalide " + strIdent + " : données incorrecte pour le mode vectoriel");
        }

        if(isFConstant)
        {
            if ((strF == "") || (strF == "*") || (wF == 0) || (stdF == 0) || (nF <= 0)){
                throw Exception("Point invalide " + strIdent + " : données incorrecte pour le mode vectoriel avec F constante");
            }
        }

        if(dec > 180.){
            dec = dec - 360.;
        }

        if(params.mUseCorrLat)
        {
            // Correction VGP exacte: Westphal, p.117 et Merill McElhinny, p.80
            // Les resultats ont ete verifies avec le logiciel PMAGTOOL a Sofia en 2001
            double latReducRadian = latReduc * radian;
            double lngReducRadian = lngReduc * radian;
            double latRadian = lat * radian;
            double lngRadian = lng * radian;

            // Calcul de la distance p du pôle (idem spherique)
            double pol = (M_PI / 2) - atan(tan(inc * radian) / 2);
            double lap = asin(sin(latRadian) * cos(pol) + cos(latRadian) * sin(pol) * cos(dec * radian));
            double beta = asin(sin(pol) * sin(dec * radian) / cos(lap));
            double lgp = lngRadian + M_PI - beta;
            if(cos(pol) >= (sin(latRadian) * sin(lap))){
                lgp = lngRadian + beta;
            }

            // Calcul de Iij et Dij corrigés (idem spherique)
            pol = acos(sin(latReducRadian) * sin(lap) + cos(latReducRadian) * cos(lap) * cos(lgp - lngReducRadian));
            inc = atan(2 * tan((M_PI / 2) - pol)) * degre;
            dec = asin(sin(lgp - lngReducRadian) * cos(lap) / sin(pol)) * degre;

            // correction VADM
            f = f * sqrt( (3. * sqrt(sin(latReducRadian)) + 1.) / (3. * sqrt(sin(latRadian)) + 1) );
        }
                 

        // l'erreur est considérée identique sur X, Y et Z dans le cas vectoriel: cf. Lanos 2004, page 77
        EctYij = sqrt((sqrt(stdF) + (2. * sqrt(f) / k)) / 3.);
        rYij = round(( nF + 2 * nd ) / 3.); // ??? vérifier la validité de cette formule
        // le poids sur Fij domine le poids sur ID
        Pij = wF;
        // les contraintes sur F dominent celles sur ID
        ch_contrainte_strati = strStratiForF;


        if(isFConstant)
        {
            f = 100;
            stdF = 0;
            nF = 1;

            // on prend la dispersion sphérique = dispersion relative x intensite (Cf. Lanos et al, 2005, page 444, section 2.3)
           EctYij = f / sqrt(k);
           rYij = nd;
           // on prends le poids sur ID
           Pij = wid;
           // les contraintes strati deviennent celles sur ID
           ch_contrainte_strati = strStratiForId;
        }
    }

    // ----------------------------------------------------------------------------------------------------------
    //  Calcul sans erreur (paramètre d'entrée)
    // ----------------------------------------------------------------------------------------------------------
    if(params.mUseErrMesure){
        EctYij = 0;
        k = 1E+30;
    }

    // ----------------------------------------------------------------------------------------------------------
    //  Sauvegarde dans Tab_Pts
    //  => On prépare en réalité ici le point qui se retrouvera dans Tab_pts
    //  ...mais a-t-on besoin des autres points (relations strati...), où se trouve tab_pts, 
    //  comment la structure des pts est définie... ?!
    // ----------------------------------------------------------------------------------------------------------
    // identificateur
    m_ident = strIdent;

    // on garde en mémoire le centre de [tdij1, tdij2] avant éventuelle restriction par l'intervalle de sélection
    m_tdijm = tm;

    // intervalle [tdij1, tdij2] a priori sur tdij : entiers (exprimés au format réel) obtenus par "floor" et "ceil" plus haut
    // On ne garde que la partie de l'intervalle [tdij1, tdij2] qui appartient à l'intervalle de sélection
    double dt = t2 - t1;
    t1 = max<double>(t1, params.mTmin);
    t2 = min<double>(t2, params.mTmax);
    m_tdij1 = t1;
    m_tdij2 = t2;

    // on détermine l'intervalle [t_floor,t_ceil] = [ min(tdij1) , max(tdij2) ] inclu dans [t_min_select,t_max_select]
    // on restreint la plage d'étude des temps au sein de l'intervalle de sélection
    if(t1 <= tFloor){
        tFloor = round(t1);
    }
    if(t2 >= tCeil){
        tCeil = round(t2);
    }

    // on initialise tdij au centre de l'intervalle a priori (éventuellement restreint)
    double t = (t1 + t2) / 2;
    m_tdij = t;
    
    // tij = tdij au départ, sera modifié si contrainte strati
    m_tij = t;
    m_Ect_tij = 0;

    // en cas de contrainte d'égalité, tij ne changent pas. Initialisation à "false"
    m_tij_maj_bay = false;
    // contrainte strati avec branchements: init à false;
    m_tij_initialise = false;

    // infos sur la distribution a priori
    m_methode_datation = strDatingMeth;
    m_param1 = param1;
    m_param2 = param2;


    double tauxP = 1;
    if(dt < (t2 - t1)){ // TODO : Jamais le cas ?! (voir calcul de dt)
        tauxP = dt / (t2 - t1);
    }
    m_Pij = tauxP * Pij;

    // on prend la chaine ch_contrainte_strati, même si c'est vide
    m_contrainte_strati = ch_contrainte_strati;

    // mesures direction
    m_Iij = inc;
    m_Dij = dec;
    m_Kij = k;
    m_rij = nd;

    // mesures intensité ou profondeur
    m_Fij = f;
    m_EctFij = stdF;
    m_rFij = nF;

    // Tab_pts[nb_ref].Yij est défini avant l'appel à Do_cravate dans Unit "traitement_spline"
    // les valeurs EctYij et rYij restent inchangées dans tous les calculs, pour chaque "Type_Var_CMT"
    m_EctYij = EctYij;
    m_rYij = rYij;

    // sommation pour le calcul de l'erreur quadratique moyenne
    moy_errij2 = moy_errij2 + (sqrt(EctYij) / rYij);

    // initialisation de la variance locale VGij = Var_G
    // Remarque: on doit multiplier Var_G par sqr(rad) si on veut comparer les erreurs SPH et VEC;
    m_VGij = params.mVarianceFixe;

    // initialisation des facteurs d'échelle Nuij du coeff de lissage alpha
    m_nuij = 1;

    // initialisation des variances temporelles Vtij dans le cas du "Fait"
    m_Vtij = 1;

    // coordonnées paramériques x(t),y(t),z(t) des points ij dans le cas IDF,
    // beaucoup plus simple et direct à déterminer que dans le cas sphérique
    if(params.mProcessType == PROCESS_TYPE_VECTORIEL)
    {
        m_XijP = f * cos(inc * radian) * cos(dec * radian);
        m_YijP = f * cos(inc * radian) * sin(dec * radian);
        m_ZijP = f * sin(inc * radian);
    }

    //   on arrondit car le calcul peut différer "légèrement" entre le système 32 et le système 64 bits.
    //   Vu le 07-10-2014 avec Lisa Schnepp en comparant les calculs sur 2 machines différentes !
   /*m_XijP = round(Fij*cos(Iij*rad)*cos(Dij*rad),-15);
   m_YijP = round(Fij*cos(Iij*rad)*sin(Dij*rad),-15);
   m_ZijP = round(Fij*sin(Iij*rad),-15);*/
}

InputPoint::~InputPoint()   
{
    
}

double InputPoint::parseDouble(const string& str)
{
    double value = 0.;
    try{
        value = stod(str);
    }catch(const invalid_argument& ia){
        cerr << "INPUT WARNING : Cannot convert " << (str != "" ? str : "(empty)") << " to double : " << ia.what() << ". Returning 0.0." << endl;
    }
    return value;
}

