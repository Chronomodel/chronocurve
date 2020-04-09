#ifndef APPLICATION_H
#define APPLICATION_H

#include "InputParams.h"
#include "InputFile.h"
#include "InputPoint.h"
#include <string>
#include <vector>

using namespace std;


class Application
{
public:
    Application();
    virtual ~Application();
    void display() const;

public:
    InputParams mParams;
    InputFile mFile;
    vector<InputPoint> mPoints; // Tab_Pts
};

#endif
