#include <DisplayManager.h>

/*******************************************************
 * Public
 ******************************************************/

DisplayManager::DisplayManager(Adafruit_SSD1306 * pDisplay)
{
    pDisplay = pDisplay;
}

void setServerState(char * serverState) 
{
    serverState = serverState;
}

void DisplayManager::displayDefaultScreen() 
{    
    pDisplay->clearDisplay();

    // Show title on first line
    addTopTitle();

    // Show server state
    pDisplay->setTextColor(WHITE);
    pDisplay->setCursor(0, computeCursorLinePosition(3));
    pDisplay->setTextWrap(0);
    pDisplay->setCursor(16, 16); // TODO : calculate center
    pDisplay->println(serverState);
    pDisplay->display();
}


void DisplayManager::displayBackupProgress(
    char * speed, 
    char * elapsedTime, 
    char * currentFileNumber, 
    char * remainingFiles)
{
    pDisplay->clearDisplay();

    // Show title on first line
    addTopTitle();

    pDisplay->setCursor(0,computeCursorLinePosition(2));
    pDisplay->write("Host script running");

    pDisplay->setCursor(0,computeCursorLinePosition(3));
    pDisplay->write("Const. speed " + *speed);
    pDisplay->setCursor(0,computeCursorLinePosition(4));
    pDisplay->write("Remaining " + *remainingFiles);
    pDisplay->setCursor(0,computeCursorLinePosition(5));
    pDisplay->write("Current file nb " + *currentFileNumber);
    pDisplay->setCursor(0,computeCursorLinePosition(6));
    pDisplay->write("Time " + *elapsedTime);
}

/*******************************************************
 * Private
 ******************************************************/

int DisplayManager::computeCursorLinePosition(int lineNumber) 
{
    return (lineNumber * 8) - 8;
}

void DisplayManager::addTopTitle()
{
    pDisplay->setTextColor(BLACK, WHITE);
    pDisplay->setTextSize(1);
    pDisplay->setCursor(0, 0);
    pDisplay->println(" USB Script Launcher ");
}

int * findCenteredCoordinates(char * text)
{
    
}
