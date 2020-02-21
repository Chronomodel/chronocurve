#include "Exception.h"

using namespace std;


Exception::Exception(const string& message) : 
message(message)
{

}

const char* Exception::what() const throw()
{
    return message.c_str();
}
