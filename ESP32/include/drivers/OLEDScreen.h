#include <Adafruit_SSD1306.h>

/*******************************************************
 * Class definition
 ******************************************************/

class OLEDScreen
{
    public:
        OLEDScreen();
        void init();
        Adafruit_SSD1306* getDisplay();
        void writeMessage(const char* message);

    private:
        Adafruit_SSD1306* pDisplay;
};