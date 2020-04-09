#ifndef INPUTPARAMS_H
#define INPUTPARAMS_H

#include "Globals.h"
#include <vector>
#include <string>

using namespace std;


class InputParams
{
public:
    InputParams();
    virtual ~InputParams();
    void setInputDataTest1();

public:
    string mFilepath;
    vector<string> mCodes;

    ProcessType mProcessType; // Type de traitement
    VariableType mVariableType; // Type de variable étudiée

    int mTmin;
    int mTmax;

    bool mSelectOuv; // bool_select_Ouv
    double mOuvMax;

    bool mUseCorrLat;
    int mResol; // résultats à 1 an , 10ans... prêt
    
    bool mUseErrMesure; // bool_err_mes

    Type mTempsType;
    bool mUseTempsBayesienFait;
    bool mUseTempsBayesienConstraint;

    Type mVarianceType; // bool_Var_G_fixe
    bool mUseVarianceIndividelle;
    double mVarianceFixe; // Var_G

    Type mCoeffLissageType;
    double mAlphaMin;
    double mAlphaMax;
    double mAlphaStep;

    int mNumIter;
};

#endif
