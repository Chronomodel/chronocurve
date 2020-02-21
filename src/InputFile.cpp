#include "InputFile.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;


InputFile::InputFile():
mLat(0.f),mLng(0.f)
{

}

InputFile::InputFile(const string& filename, const int tmin, const int tmax):
mLat(0.f),mLng(0.f)
{
    this->read(filename, tmin, tmax);
}

InputFile::~InputFile()
{
    
}

void InputFile::read(const string& filename, const int tmin, const int tmax)
{
    vector<vector<string>> rows = this->readCsv(filename);

    // 3 first lines
    mComment1 = rows[0][0];
    mComment3 = rows[1][0];
    mComment2 = rows[2][0];

    // Lat Lng
    mLat = stof(rows[3][1]);
    mLng = stof(rows[3][3]);

    // Table
    int rowIdx = 6;
    string ident = rows[rowIdx][0];

    while(ident != "end" && rowIdx < rows.size())
    {
        InputPoint point(rows[rowIdx]);
        mPoints.push_back(point);

        ++rowIdx;
        ident = rows[rowIdx][0];
    }
}

vector<vector<string>> InputFile::readCsv(const string& filename)
{
    ifstream file(filename);
    vector<vector<string>> rows;
    string line;
    string delimiter = ";";

    while(getline(file, line))
    {
        vector<string> row;
        boost::algorithm::split(row, line, boost::is_any_of(delimiter));
        rows.push_back(row);
    }
    
    file.close();
    return rows;
}

void InputFile::display() const
{
    for(int i=0; i<mPoints.size(); ++i)
    {
        const InputPoint& point = mPoints[i];

        cout << point.mIdent << "\t |"
            << point.mCode << "\t |"
            << point.mLat << "\t |"
            << point.mLng << "\t |"
            << point.mInc << "\t |"
            << point.mDec << "\t |"
            << point.mK << "\t |"
            << point.mND << "\t |"
            << point.mWID << "\t |"
            << point.mF << "\t |"
            << point.mStdF << "\t |"
            << point.mNF << "\t |"
            << point.mWF << "\t |"
            << point.mDatingMeth << "\t |"
            << point.mParam1 << "\t |"
            << point.mParam2 << "\t |"
            << point.mT1 << "\t |"
            << point.mT2 << "\t |"
            << point.mTm << "\t |"
            << point.mStratiForId << "\t |"
            << point.mStratiForF << "\t |"
            << endl;
    }
}
