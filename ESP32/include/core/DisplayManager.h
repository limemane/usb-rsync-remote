#include <OLEDScreen.h>

class DisplayManager
{
    public:
        DisplayManager(Adafruit_SSD1306 * pDisplay);
        void setServerState(char * serverState);
        void displayDefaultScreen();
        void displayBackupProgress(char * speed, char * elapsedTime, char * currentFileNumber, char * remainingFiles);
        
    private:
        Adafruit_SSD1306 * pDisplay;
        int computeCursorLinePosition(int lineNumber);
        void addTopTitle();
        char * serverState;
};