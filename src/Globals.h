#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
//#include <cmath>

#define radian (M_PI / 180)
#define degre (180 / M_PI)

enum ProcessType
{
    PROCESS_TYPE_UNIVARIE = 'U',
    PROCESS_TYPE_SPHERIQUE = 'S',
    PROCESS_TYPE_VECTORIEL = 'V',
};

enum VariableType // Type_var_cmt
{
    VAR_TYPE_INCLINAISON = 'I',
    VAR_TYPE_DECLINAISON = 'D',
    VAR_TYPE_INTENSITE = 'F', 
    VAR_TYPE_PROFONDEUR = 'P',
};

enum Type
{
    TYPE_FIXE = 'F',
    TYPE_BAYESIEN = 'B',
};

// bool_spline_spherique : true que si mProcessType = PROCESS_TYPE_SPHERIQUE

std::string upper(const std::string& s);
bool string_contains(const std::string& str, const std::string& needle);
bool string_contains(const std::string& str, const char* needle);

/*template<class T> 
inline const T& max(const T& a, const T& b)
{
    return (a < b) ? b : a;
}

template<class T> 
inline const T& min(const T& a, const T& b)
{
    return (a < b) ? a : b;
}*/

#endif