#include "Globals.h"
#include <cctype>
#include <algorithm>
#include <regex>

//#include <stdexcept>
//#include <iostream>
//#include <cmath>

using namespace std;

string upper(const string& str)
{
    string out;
    transform(str.begin(), str.end(), back_inserter(out), ::toupper);
    return out;
}

bool string_contains(const string& str, const string& needle)
{
    size_t found = str.find(needle);
    return (found != string::npos);
}

bool string_contains(const string& str, const char* needle)
{
    return string_contains(str, string(needle));
}

vector<string> explode(const string& str, const string& delimiter)
{
	// Possible avec Boost
	//vector<string> row;
   	//boost::algorithm::split(row, line, boost::is_any_of(delimiter));

	// Explications sur la regex utilisée ici : 
    // https://stackoverflow.com/questions/11310947/splitting-a-line-of-a-csv-file-into-a-stdvector
	const regex re{"((?:[^\\\\" + delimiter + "]|\\\\.)*?)(?:" + delimiter + "|$)"};
   	vector<string> exploded{sregex_token_iterator(str.begin(), str.end(), re, 1), sregex_token_iterator()};
   	return exploded;
}