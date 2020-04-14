#include "Application.h"
#include <iostream>
#include <exception>
#include <cmath>

using namespace std;


Application::Application() 
{
    // For dev : use test params
    mParams.setInputDataTest1();

    // Lecture brute (strings) du fichier d'entrée
    mFile = InputFile(mParams.mFilepath);
    mFile.displayPoints();

    // Lecture des points, corrections, et création de Tab_Pts
    mPoints.clear();

    for(int i=0; i<mFile.mPointsStr.size(); ++i)
    {
        // Une série de codes spécifiques est précisée.
        // Ceci permet de ne prendre en compte que les sous-ensemble de points correspondant à ces codes
        if(mParams.mCodes.size() > 0)
        {
            vector<string> pointValues = mFile.mPointsStr[i];
            string code = pointValues[1];
            if(find(mParams.mCodes.begin(), mParams.mCodes.end(), code) == mParams.mCodes.end()){
                continue; // Le code du point n'est pas dans la liste des codes spécifiés
            }
        }

        try{
            cout << "=> Parsing point " << i << "..." << endl;
            InputPoint point(i, mFile, mParams, mTfloor, mTceil, mMoyErrij2);
            mPoints.push_back(point);
        }catch(const exception& e){
            cerr << "Point " << i << " not saved " << " : " << e.what() << endl;
        }
    }

    // --------------------------------------------------------------------------------------------
    //  Distribution des données sur le temps à partir des densités a priori p(tij)
    // --------------------------------------------------------------------------------------------
    Density defaultDensity;
    int size = round(mTceil) - round(mTfloor) + 1;
    mTabDensityTij = vector<Density>(size, defaultDensity);
    
    for(int k=0; k<mPoints.size(); ++k)
    {
        double j_max = mPoints[k].m_densite_priori_tdij.size();

        // Calcul de la somme des densités pour le point k
        long double som_densij = 0;
        for(int j=0; j<j_max; ++j){
            som_densij += mPoints[k].m_densite_priori_tdij[j];
        }

        for(int j=0; j<j_max; ++j)
        {
            // normalisation à 1
            mPoints[k].m_densite_priori_tdij[j] /= som_densij;

            // cumul des densités et du nbre de points par année i
            // calcul correct ?
            int i = round(mPoints[k].m_tdij1 + j - 1) - round(mTfloor);

            // += alors que pas encore initialisé ?
            mTabDensityTij[i].p += mPoints[k].m_densite_priori_tdij[j];
            mTabDensityTij[i].n += 1;
        }
    }

    // --------------------------------------------------------------------------------------------
    //  Réduction des temps
    // --------------------------------------------------------------------------------------------
    // t_span (en années) sert à ré-échelonner les temps entre 0 et 1 avec la fonction temps_reduit
    mTspan = mTceil - mTfloor;

    // sauvegarde temps réduits
    for(int k=0; k<mPoints.size(); ++k)
    {
        mPoints[k].m_tdij = tempsReduit(mPoints[k].m_tdij);
        mPoints[k].m_tdij1 = tempsReduit(mPoints[k].m_tdij1);
        mPoints[k].m_tdij2 = tempsReduit(mPoints[k].m_tdij2);
        mPoints[k].m_tdijm = tempsReduit(mPoints[k].m_tdijm);
        mPoints[k].m_tij = tempsReduit(mPoints[k].m_tij);
    }
   
    // Normalisation des pondérations Pij des points Yij
    double somP = 0;
    for(int k=0; k<mPoints.size(); ++k)
    {
        somP += mPoints[k].m_Pij;
    }
    for(int k=0; k<mPoints.size(); ++k)
    {
        mPoints[k].m_Pij *= mPoints.size() / somP;
    }

    // erreur quadratique moyenne sur tous les points ij
    mMoyErrij2 = mMoyErrij2 / mPoints.size();

    // --------------------------------------------------------------------------------------------
    //  Prise en compte des contraintes stratigraphiques 
    // --------------------------------------------------------------------------------------------
    for(int k=0; k<mPoints.size(); ++k)
    {
        string contrainteStr = mPoints[k].m_contrainte_strati;

        mPoints[k].m_tij_avant = vector<int>(10, 0);
        mPoints[k].m_tij_pendant = vector<int>(10, 0);
        mPoints[k].m_tij_apres = vector<int>(10, 0);
        
        vector<string> contraintes = explode(contrainteStr, "/");
    }

}

double Application::tempsReduit(double t) const
{
    return (t - (double)mTfloor) / (double)mTspan;
}

double Application::tempsAnnee(double t) const
{
    return t * (double)mTspan + (double)mTfloor;
}


Application::~Application() 
{

}

void Application::display() const
{
    cout << "-------------------------------------------------" << endl;
    cout << "Tab_Pts créé avec " << mPoints.size() << "/" << mFile.mPointsStr.size() << " points retenus" << endl;
    cout << "-------------------------------------------------" << endl;
}