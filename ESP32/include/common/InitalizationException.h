#include <exception>

using namespace std;

class InitializationException : public exception
{
    public:
        InitializationException(const char * message);
        const char* what();
        
    private:
        char message[128];
};