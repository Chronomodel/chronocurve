#ifndef INPUTFILE_H
#define INPUTFILE_H

#include "InputPoint.h"
#include <string>
#include <vector>

using namespace std;


class InputFile
{
public:
    InputFile();
    InputFile(const string& filename, const int tmin, const int tmax);
    virtual ~InputFile();

    void read(const string& filename, const int tmin, const int tmax);
    void display() const;

protected:
    vector<vector<string>> readCsv(const string& filename);

public:
    string mComment1;
    string mComment2;
    string mComment3;

    float mLat;
    float mLng;

    vector<InputPoint> mPoints;
};

#endif
