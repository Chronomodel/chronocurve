#include "InputFile.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <exception>
#include <algorithm>
#include <regex>
//#include <boost/algorithm/string.hpp>

using namespace std;


InputFile::InputFile():
mLatReduc(0.f),mLngReduc(0.f)
{

}

InputFile::InputFile(const string& filename):
mLatReduc(0.f),mLngReduc(0.f)
{
    this->read(filename);
}

InputFile::~InputFile()
{
    
}

void InputFile::read(const string& filename)
{
    vector<vector<string>> rows = this->readCsv(filename);

    // 3 first lines
    mComment1 = rows[0][0];
    mComment3 = rows[1][0];
    mComment2 = rows[2][0];

    // Lat Lng
    mLatReduc = stof(rows[3][1]);
    mLngReduc = stof(rows[3][3]);

    // Table
    int rowIdx = 6;
    string ident = rows[rowIdx][0];
    mPointsStr.clear();

    while(ident != "end" && rowIdx < rows.size())
    {
        mPointsStr.push_back(rows[rowIdx]);
        ++rowIdx;
        ident = rows[rowIdx][0];
    }
}

vector<vector<string>> InputFile::readCsv(const string& filename)
{
    ifstream file(filename);
    if(!file.is_open()){
        throw Exception("Input file cannot be opened");
    }

    vector<vector<string>> rows;
    string line;
    //string delimiter = ";";

    // Explications sur la regex utilisée ici : 
    // https://stackoverflow.com/questions/11310947/splitting-a-line-of-a-csv-file-into-a-stdvector
    const regex re{"((?:[^\\\\;]|\\\\.)*?)(?:;|$)"};

    while(getline(file, line))
    {
        //vector<string> row;
        //boost::algorithm::split(row, line, boost::is_any_of(delimiter));

        // Explications sur la regex utilisée ici : 
        // https://stackoverflow.com/questions/11310947/splitting-a-line-of-a-csv-file-into-a-stdvector
        vector<string> row{sregex_token_iterator(line.begin(), line.end(), re, 1), sregex_token_iterator()};

        rows.push_back(row);
    }
    
    file.close();
    return rows;
}


void InputFile::displayPoints() const
{
    for(int i=0; i<mPointsStr.size(); ++i)
    {
        const vector<string>& point = mPointsStr[i];

        cout << "Point " << i << ":\t | " 
            << point[0] << "\t | "
            << point[1] << "\t | "
            << point[2] << "\t | "
            << point[3] << "\t | "
            << point[4] << "\t | "
            << point[5] << "\t | "
            << point[6] << "\t | "
            << point[7] << "\t | "
            << point[8] << "\t | "
            << point[9] << "\t | "
            << point[10] << "\t | "
            << point[11] << "\t | "
            << point[12] << "\t | "
            << point[13] << "\t | "
            << point[14] << "\t | "
            << point[15] << "\t | "
            << point[16] << "\t | "
            << point[17] << "\t | "
            << point[18] << "\t | "
            << point[19] << "\t | "
            << point[20] << "\t | "
            << endl;

        cout << "---------------------------------------" << endl;
    }
}
