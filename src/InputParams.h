#ifndef INPUTPARAMS_H
#define INPUTPARAMS_H

#include "InputFile.h"
#include <string>

using namespace std;


class InputParams
{
public:
    enum Mode 
    {
        MODE_UNIVARIE = 'U',
        MODE_SPHERIQUE = 'S',
        MODE_VECTORIEL = 'V',
    };

    enum UnivarieMode 
    {
        UNIV_MODE_INCLINAISON = 'I',
        UNIV_MODE_DECLINAISON = 'D',
        UNIV_MODE_CHAMP = 'F',
        UNIV_MODE_PROFONDEUR = 'P',
    };

    enum Type
    {
        TYPE_FIXE = 'F',
        TYPE_BAYESIEN = 'B',
    };

    InputParams();
    virtual ~InputParams();
    void init();
    void display() const;

public:
    InputFile mFile;
    string mFilepath;

    Mode mMode;
    UnivarieMode mUnivMode;

    int mTmin;
    int mTmax;

    bool mUseCorrLat;
    int mResol; // résultats à 1 an , 10ans... prêt
    
    bool mUseErrMesure;
    Type mTempsType;
    bool mUseTempsBayesienFait;
    bool mUseTempsBayesienConstraint;

    Type mVarianceType;
    bool mUseVarianceIndividelle;
    float mVarianceFixe;

    Type mCoeffLissageType;
    float mAlphaMin;
    float mAlphaMax;
    float mAlphaStep;

    int mNumIter;
};

#endif
