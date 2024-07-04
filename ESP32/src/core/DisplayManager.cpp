#include <DisplayManager.h>

/*******************************************************
 * Public
 ******************************************************/

DisplayManager::DisplayManager(OLEDScreen * pOledScreen)
{
    pOledScreen = pOledScreen;
}

void setConnectionStatus(char * connectionStatus)
{
    connectionStatus = connectionStatus;
}

void setServerState(char * serverState) 
{
    serverState = serverState;
}

void DisplayManager::displayBackupProgress(
    char * speed, 
    char * elapsedTime, 
    char * currentFileNumber, 
    char * remainingFiles)
{
    Adafruit_SSD1306 * display = pOledScreen->getDisplay();
    display->setCursor(0,0);
    display->write("Construction speed ");
    // TODO : show every values
}

/*******************************************************
 * Private
 ******************************************************/

void DisplayManager::updateStatusAndState() 
{
    Adafruit_SSD1306 * display = pOledScreen->getDisplay();
    display->setCursor(0,0);
    display->write(connectionStatus);
    display->setCursor(0,8);
    display->write(serverState);
}
