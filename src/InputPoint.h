#ifndef INPUTPOINT_H
#define INPUTPOINT_H

#include <string>
#include <vector>

using namespace std;


class InputPoint
{
public:
    enum Mode 
    {
        MODE_INCLINAISON = 'I',
        MODE_DECLINAISON = 'D',
        MODE_CHAMP = 'F',
    };

    InputPoint();
    InputPoint();
    virtual ~InputPoint();

private:
    float parseFloat(const string& str);
    void setValuesFromStrings(const vector<string>& values, const float lat, const float lng);

public:
    string mIdent;
    string mCode; // ch_code_select
    
    float mLat; // ch_lati
    float mLng; // ch_longi

    float mInc; // ch_Iij
    float mDec; // ch_Dij
    float mK; // ch_Kij
    float mND; // ch_rij
    float mWID; // ch_WIDij
    float mF; // ch_Fij
    float mStdF; // ch_EctFij
    float mNF; // ch_rFij
    float mWF; // ch_WFij
    
    string mDatingMeth; // ch_methode_datation
    float mParam1; // ch_param1
    float mParam2; // ch_param2
    float mT1; // ch_tdij1
    float mT2; // ch_tdij2
    float mTm; // ch_tdijm

    string mStratiForId; // ch_contrainte_strati_ID
    string mStratiForF; // ch_contrainte_strati_F
};

#endif
