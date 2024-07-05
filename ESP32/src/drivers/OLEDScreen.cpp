#include <Adafruit_SSD1306.h>
#include "OLEDScreen.h"
#include "InitalizationException.h"

/*******************************************************
 * Constants
 ******************************************************/

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 

/*******************************************************
 * Class methods
 ******************************************************/

OLEDScreen::OLEDScreen() 
{
    pDisplay = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
}

void OLEDScreen::init()
{
    if(pDisplay->begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
    { 
        pDisplay->clearDisplay();
        pDisplay->setTextSize(1);      // 2:1 pixel scale
        pDisplay->setTextColor(WHITE); // Draw white text
        pDisplay->setCursor(0, 0);     // Start at top-left corner
        pDisplay->cp437(true);         // Use full 256 char 'Code Page 437' font
        pDisplay->display();
    }
    else 
    {
        throw InitializationException("OLED display has gone berzerk and thus was not initialized");
    }
}

Adafruit_SSD1306* OLEDScreen::getDisplay()
{
    return pDisplay;
}

void OLEDScreen::writeMessage(const char* message)
{
    pDisplay->clearDisplay();
    pDisplay->setCursor(0, 0);
    pDisplay->write(message);
    pDisplay->display();
}