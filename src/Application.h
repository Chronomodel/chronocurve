#ifndef APPLICATION_H
#define APPLICATION_H

#include "Globals.h"
#include "InputParams.h"
#include "InputFile.h"
#include "InputPoint.h"
#include <string>
#include <vector>


class Application
{
public:
    Application();
    virtual ~Application();
    
    double tempsReduit(double t) const;
    double tempsAnnee(double t) const;

    void display() const;

public:
    InputParams mParams;
    InputFile mFile;

    int mTfloor;
    int mTceil;
    int mTspan;

    double mMoyErrij2; // moy_errij2

    std::vector<InputPoint> mPoints; // Tab_Pts
    std::vector<Density> mTabDensityTij; // Tab_densite_tij
};

#endif
