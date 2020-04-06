#include "ChronocurveConfig.h"
#include "InputFile.h"
#include "InputParams.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void setInputDataTest1(InputParams& params)
{
    params.mFilepath = "../tests/input.csv";

    params.mTmin = -100000;
    params.mTmax = 10000;

    params.mUseCorrLat = true;
    params.mResol = 0;

    params.mUseErrMesure = true;
    params.mTempsType = InputParams::TYPE_BAYESIEN;
    params.mUseTempsBayesienFait = true;
    params.mUseTempsBayesienConstraint = true;

    params.mVarianceType = InputParams::TYPE_BAYESIEN;
    params.mUseVarianceIndividelle = true;
    params.mVarianceFixe = 1.f;

    params.mCoeffLissageType = InputParams::TYPE_BAYESIEN;
    params.mAlphaMin = 0.000001;
    params.mAlphaMax = 0.000001;
    params.mAlphaStep = 0.1;

    params.mNumIter = 10000;
}

int main(int argc, char *argv[])
{
    cout << "---------------------------------------------------------------------" << endl;
    cout << "=> Chronocurve " << Chronocurve_VERSION_MAJOR << "." << Chronocurve_VERSION_MINOR << endl;
    cout << "---------------------------------------------------------------------" << endl;
        
    InputParams params;
    setInputDataTest1(params);
    params.init();
    params.display();

    cout << "---------------------------------------------------------------------" << endl;
    return 1;
}
