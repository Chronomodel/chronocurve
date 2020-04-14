#include "CsvReader.h"
#include "Exception.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <exception>
#include <algorithm>
#include <regex>

using namespace std;


CsvReader::CsvReader(){}

vector<vector<string>> CsvReader::readFile(const string& filename, const string& delimiter = ";")
{
    // -----------------------------------------------------------------
    //  If the file has been already read,  return it !
    // -----------------------------------------------------------------
    map< string, vector<vector<string>> >::const_iterator it = mFiles.find(filename);
    if(it != mFiles.end()){
        return it->second;
    }

    cout << "=> Reading file : " << filename << endl;

    // -----------------------------------------------------------------
    //  Read the file
    // -----------------------------------------------------------------
    ifstream file(filename);
    if(!file.is_open()){
        throw Exception("Input file cannot be opened : " + filename);
    }

    vector<vector<string>> rows;   
    string line;

    // Explications sur la regex utilisée ici : 
    // https://stackoverflow.com/questions/11310947/splitting-a-line-of-a-csv-file-into-a-stdvector
    const regex re{"((?:[^\\\\" + delimiter + "]|\\\\.)*?)(?:" + delimiter + "|$)"};

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

    mFiles.insert(pair<string, vector<vector<string>>>(filename, rows));

    cout << "=> Lines read as string : " << rows.size() << endl;

    return rows;
}

vector<vector<double>> CsvReader::readFileAsDouble(const string& filename, const string& delimiter = ";")
{
    // -----------------------------------------------------------------
    //  If the file has been already read, return it !
    // -----------------------------------------------------------------
    map< string, vector<vector<double>> >::const_iterator it = mFilesDouble.find(filename);
    if(it != mFilesDouble.end()){
        return it->second;
    }

    const vector<vector<string>> csv = CsvReader::readFile(filename, delimiter);
    vector<vector<double>> result;

    for(int r=0; r<csv.size(); ++r)
    {
        const vector<string>& rowString = csv[r];
        vector<double> rowDouble;
        bool rowIsValid = true;

        for(int c=0; c<rowString.size(); ++c)
        {
            try{
                double value = stod(rowString[c]);
                rowDouble.push_back(value);
            }catch(const invalid_argument& ia){
                if(c == 0){
                    rowIsValid = false;
                }
            }
        }
        if(rowIsValid){
            result.push_back(rowDouble);
        }
    }

    mFilesDouble.insert(pair<string, vector<vector<double>>>(filename, result));

    cout << "=> Lines read as double : " << result.size() << endl;

    return result;
}
