#include "InputPoint.h"
#include "Exception.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>

using namespace std;


InputPoint::InputPoint():
mIdent(""),
mCode(""),
mLat(0),
mLng(0),
mInc(0),
mDec(0),
mK(0),
mND(0),
mWID(0),
mF(0),
mStdF(0),
mNF(0),
mWF(0),
mDatingMeth(""),
mParam1(""),
mParam2(""),
mT1(""),
mT2(""),
mTm(""),
mStratiForId(""),
mStratiForF("")
{

}

InputPoint::InputPoint()
{
    
}

InputPoint::~InputPoint()   
{
    
}

float InputPoint::parseFloat(const string& str)
{
    float value = 0.;
    try{
        value = stof(str);
    }catch(const invalid_argument& ia){
        cerr << "INPUT ERROR : Cannot convert " << str << " to float : " << ia.what() << ". Returning 0.0." << endl;
    }
    return value;
}

/**
* Extrait de U_cmt_lit
*/
void InputPoint::adjust(const vector<string>& values, const float latRed, const float lngRed, const int tmin, const int tmax)
{
    // ---------------------------------------------------------
    // On commence par lire les variables sous forme de strings avec des noms identifiables
    // ---------------------------------------------------------
    string strIdent = values[0];
    string strCode = values[1];

    string strLat = values[2];
    string strLng = values[3];
    string strInc = values[4];
    string strDec = values[5];
    string strK = values[6];
    string strND = values[7];
    string strWID = values[8];
    string strF = values[9];
    string strStdF = values[10];
    string strNF = values[11];
    string strWF = values[12];

    string strDatingMeth = toupper(values[13]);
    string strParam1 = values[14];
    string strParam2 = values[15];
    string strT1 = values[16];
    string strT2 = values[17];
    string strTm = values[18];

    string strStratiForId = toupper(values[19]);
    string strStratiForF = toupper(values[20]);

    // ---------------------------------------------------------
    // On convertit les valeurs numériques
    // ---------------------------------------------------------
    mLat = this->parseFloat(strLat);
    mLng = this->parseFloat(strLng);

    mInc = this->parseFloat(strInc);
    mDec = this->parseFloat(strDec);
    mK = this->parseFloat(strK);
    mND = this->parseFloat(strND);
    mWID = this->parseFloat(strWID);
    mF = this->parseFloat(strF);
    mStdF = this->parseFloat(strStdF);
    mNF = this->parseFloat(strNF);
    mWF = this->parseFloat(strWF);

    mParam1 = this->parseFloat(strParam1);
    mParam2 = this->parseFloat(strParam2);

    // Encadrement en année exacte en restant au format réel
    mT1 = floorf(this->parseFloat(strT1));
    mT2 = ceilf(this->parseFloat(strT2));

    mTm = this->parseFloat(strTm);

    // ---------------------------------------------------------
    //  Vérification des temps
    // ---------------------------------------------------------
    if (mT1 > mT2){
        throw Exception("Problème au point " + mIdent + " : inversion de date");
    }

    // ---------------------------------------------------------

    float radian = M_PI / 180;
    bool selectRef = false;
    // TODO : global Tab_code_select
    // TODO : global bool_select_Ouv
    // TODO : type_var_CMT ??
    // TODO : global bool_corr_latitude (UI checkbox)


    // ----------------------------------------------------------------------------------------------------------
    //  TO CHECK : On ne retient que les points compris (totalement ou partiellement) entre tmin et tmax,
    // ----------------------------------------------------------------------------------------------------------
    if((strT1 != "") && (strT1 != "*") && (strT2 != "") && (strT2 != "*") && (mT2 >= tmin) && (mT1 <= tmax))
    {
        if(Tab_code_select[11] != ""){
            for(int i=0; i<10; ++i){
                selectRef |= (Tab_code_select[i] == mCode);
            }
        }
    }

    // ----------------------------------------------------------------------------------------------------------
    // Sélection éventuelle par zone géographique
    // ----------------------------------------------------------------------------------------------------------
    if(bool_select_Ouv)
    {
        float latRedRadian = latRed * radian;
        float lngRedRadian = lngRed * radian;
        float latRadian = mLat * radian;
        float lngRadian = mLng * radian;
        float ouv = (cosf(latRadian) * cosf(latRedRadian) * cosf(lngRadian - lngRedRadian)) + (sinf(latRadian) * sinf(latRedRadian));
        float ouv = arccosf(ouv) * 180 / M_PI;
        if(ouv >= select_ouvmin && ouv < select_ouvmin) // ?????
        {
            selectRef = true;
        }
    }

    // ----------------------------------------------------------------------------------------------------------
    // Sélection du point de référence
    // ----------------------------------------------------------------------------------------------------------
    if(selectRef)
    {
        if(type_var_CMT == InputPoint::MODE_INCLINAISON)
        {
            if ((strInc == '') || (strInc == '*') || (mWID = 0) || (mK = 0) || (mND <= 1)){
                throw Exception("Point invalide " + mIdent + " : données incorrecte pour le mode inclinaison");
            }

            if bool_corr_latitude then  Iij:=Iij + 0.5*(3*sqr(cos(Iij*rad))+1)*(Lati_reduc-Lati);

            // Yij:=Fij;  Cette opération est effectuée avant l'appel à "Do_cravate" dans Unit "traitement_spline"
            // pour tous les cas de type_Var_CMT

            // qu'il s'agisse de struct. en place ou de matériaux déplacés, on rentre toujours K dans le fichier csv
            // K est alors calculé comme: K = (1/sqr(SI))*rad où SI est l'écart-type (au sens de la dispersion) sur l'inclinaison I
            EctYij:=(1/sqrt(Kij))*Deg;
            rYij:=rij;
            Pij:=WIDij;
            ch_contrainte_strati:=ch_contrainte_strati_ID;
        }
    }



    /*mIdent = values[0];
    mCode = values[1];

    mLat = this->parseFloat(values[2]);
    mLng = this->parseFloat(values[3]);
    mInc = this->parseFloat(values[4]);
    mDec = this->parseFloat(values[5]);
    mK = this->parseFloat(values[6]);
    mND = this->parseFloat(values[7]);
    mWID = this->parseFloat(values[8]);
    mF = this->parseFloat(values[9]);
    mStdF = this->parseFloat(values[10]);
    mNF = this->parseFloat(values[11]);
    mWF = this->parseFloat(values[12]);

    mDatingMeth = values[13];
    mParam1 = this->parseFloat(values[14]);
    mParam2 = this->parseFloat(values[15]);
    mT1 = floorf(this->parseFloat(values[16]));
    mT2 = ceilf(this->parseFloat(values[17]));
    mTm = this->parseFloat(values[18]);

    mStratiForId = values[19];
    mStratiForF = values[20];*/
}
