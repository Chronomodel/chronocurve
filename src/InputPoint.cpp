#include "InputPoint.h"
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

InputPoint::InputPoint(const vector<string>& values)
{
    mIdent = values[0];
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
    mParam1 = values[14];
    mParam2 = values[15];
    mT1 = values[16];
    mT2 = values[17];
    mTm = values[18];

    mStratiForId = values[19];
    mStratiForF = values[20];
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

void InputPoint::adjust(const float latRed, const float lngRed, const int tmin, const int tmax)
{
    // Global
    Tab_code_select
    bool_select_Ouv

    bool selectRef = false;
    float radian = M_PI / 180;

    // ----------------------------------------------------------------------------------------------------------
    // On ne retient que les points compris (totalement ou partiellement) entre tmin et tmax,
    // ----------------------------------------------------------------------------------------------------------
    if((mT1 != "") && (mT1 != "*") && (mT2 != "") && (mT2 != "*") && (mT2 >= tmin) && (mT1 <= tmax))
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
}
