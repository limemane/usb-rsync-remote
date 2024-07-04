#include <exception>

using namespace std;

class InitializationException : public exception
{
    public:
        InitializationException(char * message);
        const char* what();
        
    private:
        char * message;
};