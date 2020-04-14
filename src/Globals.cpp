#include "Globals.h"
#include <algorithm>

using namespace std;

string upper(const string& s)
{
    string out;
    transform(s.begin(), s.end(), back_inserter(out), toupper);
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