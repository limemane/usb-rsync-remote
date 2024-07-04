#include<Adafruit_SSD1306.h>

class DisplayManager
{
    public:
        DisplayManager(Adafruit_SSD1306 * pDisplay);
        void setServerState(const char * serverState);
        void displayDefaultScreen();
        void displayBackupProgress(const char * speed, const char * elapsedTime, const char * currentFileNumber, const char * remainingFiles);
        
    private:
        Adafruit_SSD1306 * pDisplay;
        int computeCursorLinePosition(int lineNumber);
        void addTopTitle();
        const char * serverState;
};