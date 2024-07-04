#include <exception>
#include "InitalizationException.h"
#include <string.h>

using namespace std;

InitializationException::InitializationException(const char * message)
{
    // String copy so constructor can either receive a literal string or a char pointer containing the error message (cf doudou)
    strncpy(this->message, message, 127);
    this->message[127] = 0;
}

const char* InitializationException::what() 
{
    return this->message;
}

