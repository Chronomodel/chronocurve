#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <exception>


class Exception: public std::exception
{
public:
    explicit Exception(const std::string& message);
    virtual const char* what() const throw();

private:
    std::string message;
};

#endif
