#include "Globals.h"
#include <algorithm>

using namespace std;

string upper(const string& s)
{
    string out;
    transform(s.begin(), s.end(), back_inserter(out), toupper);
    return out;
}