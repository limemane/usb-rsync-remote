#include <DisplayManager.h>

/*******************************************************
 * Public
 ******************************************************/

DisplayManager::DisplayManager(Adafruit_SSD1306* pDisplay)
{
    this->pDisplay = pDisplay;
}

void DisplayManager::setServerState(const char* serverState) 
{
    this->serverState = serverState;
}

void DisplayManager::displayDefaultScreen() 
{    
    pDisplay->clearDisplay();

    // Show title on first line
    addTopTitle();

    // Show server state
    pDisplay->setTextColor(WHITE);
    pDisplay->setCursor(0, computeCursorLinePosition(5));
    pDisplay->println(serverState);
    pDisplay->display();
}


void DisplayManager::displayBackupProgress(
    const char* speed, 
    const char* elapsedTime, 
    const char* currentFileNumber, 
    const char* remainingFiles)
{
    pDisplay->clearDisplay();

    // Show title on first line
    addTopTitle();

    pDisplay->setTextColor(WHITE);
    pDisplay->setCursor(0,computeCursorLinePosition(2));
    pDisplay->write("       Running");

    pDisplay->setCursor(0,computeCursorLinePosition(4));
    pDisplay->write(speed);
    pDisplay->setCursor(0,computeCursorLinePosition(5));
    pDisplay->write(remainingFiles);
    pDisplay->setCursor(0,computeCursorLinePosition(6));
    pDisplay->write(currentFileNumber);
    pDisplay->setCursor(0,computeCursorLinePosition(7));
    pDisplay->write(elapsedTime);

    pDisplay->display();
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
