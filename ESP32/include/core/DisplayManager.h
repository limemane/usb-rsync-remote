#include <OLEDScreen.h>

class DisplayManager
{
    public:
        DisplayManager(OLEDScreen * pOledScreen);
        void setConnectionStatus(char * connectionStatus);
        void setServerState(char * serverState);
        void displayBackupProgress(char * speed, char * elapsedTime, char * currentFileNumber, char * remainingFiles);
        
    private:
        OLEDScreen * pOledScreen;
        void updateStatusAndState();
        char * connectionStatus;
        char * serverState;
};