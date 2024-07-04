#include <exception>
#include "InitalizationException.h"

using namespace std;

InitializationException::InitializationException(char * message)
{
    this->message = message;
}

const char* InitializationException::what() 
{
    return this->message;
}

