#ifndef INPUTPOINT_H
#define INPUTPOINT_H

#include <string>
#include <vector>

using namespace std;


class InputPoint
{
public:
    InputPoint();
    InputPoint(const vector<string>& values);
    virtual ~InputPoint();

private:
    float parseFloat(const string& str);
    void adjust(const float lat, const float lng);

public:
    string mIdent;
    string mCode;
    
    float mLat;
    float mLng;

    float mInc;
    float mDec;
    float mK;
    float mND;
    float mWID;
    float mF;
    float mStdF;
    float mNF;
    float mWF;
    
    string mDatingMeth;
    string mParam1;
    string mParam2;
    string mT1;
    string mT2;
    string mTm;

    string mStratiForId;
    string mStratiForF;
};

#endif
