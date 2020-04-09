#include "Application.h"
#include <iostream>
#include <exception>

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

    double tFloor;
    double tCeil;
    double moy_errij2 = 0.;

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
            InputPoint point(i, mFile, mParams, tFloor, tCeil, moy_errij2);
            mPoints.push_back(point);
        }catch(const exception& e){
            cerr << "Point " << i << " not saved " << " : " << e.what() << endl;
        }
    }


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