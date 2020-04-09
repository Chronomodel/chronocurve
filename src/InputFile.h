#ifndef INPUTFILE_H
#define INPUTFILE_H

#include <string>
#include <vector>

using namespace std;


class InputFile
{
public:
    InputFile();
    InputFile(const string& filename);
    virtual ~InputFile();

    void read(const string& filename);
    vector<vector<string>> readCsv(const string& filename);
    void displayPoints() const;

public:
    string mComment1;
    string mComment2;
    string mComment3;

    double mLatReduc;
    double mLngReduc;

    vector<vector<string>> mPointsStr;
};

#endif
