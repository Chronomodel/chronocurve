#ifndef INPUTFILE_H
#define INPUTFILE_H

#include <string>
#include <vector>


class InputFile
{
public:
    InputFile();
    InputFile(const std::string& filename);
    virtual ~InputFile();

    void read(const std::string& filename);
    void displayPoints() const;

public:
    std::string mComment1;
    std::string mComment2;
    std::string mComment3;

    double mLatReduc;
    double mLngReduc;

    std::vector<std::vector<std::string>> mPointsStr;
};

#endif
