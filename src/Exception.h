#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <exception>

using namespace std;


class Exception: public exception
{
public:
    explicit Exception(const string& message);
    virtual const char* what() const throw();

private:
    string message;
};

#endif
