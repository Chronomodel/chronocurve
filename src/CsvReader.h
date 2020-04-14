#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <vector>
#include <map>

class CsvReader
{
private:
    CsvReader();
    
public:
    static std::vector<std::vector<std::string>> readFile(const std::string& filename, const std::string& delimiter);
    static std::vector<std::vector<double>> readFileAsDouble(const std::string& filename, const std::string& delimiter);

public:
    inline static std::map< std::string, std::vector<std::vector<std::string>> > mFiles;
    inline static std::map< std::string, std::vector<std::vector<double>> > mFilesDouble;
};

#endif
