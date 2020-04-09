#include "InputParams.h"


InputParams::InputParams()
{

}

InputParams::~InputParams()
{
    
}

void InputParams::setInputDataTest1()
{
    mFilepath = "../tests/input.csv";
    //mCodes // leave empty to select all

    mProcessType = PROCESS_TYPE_UNIVARIE;
    mVariableType = VAR_TYPE_INCLINAISON;

    mTmin = -100000;
    mTmax = 10000;

    mSelectOuv = false;
    mOuvMax= 0.;

    mUseCorrLat = true;
    mResol = 0;

    mUseErrMesure = true;
    mTempsType = TYPE_BAYESIEN;
    mUseTempsBayesienFait = true;
    mUseTempsBayesienConstraint = true;

    mVarianceType = TYPE_BAYESIEN;
    mUseVarianceIndividelle = true;
    mVarianceFixe = 1.;

    mCoeffLissageType = TYPE_BAYESIEN;
    mAlphaMin = 0.000001;
    mAlphaMax = 0.000001;
    mAlphaStep = 0.;

    mNumIter = 10000;
}
