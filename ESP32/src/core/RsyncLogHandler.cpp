#include "RsyncLogHandler.h"
#include <string.h>


RsyncLogHandler::RsyncLogHandler() 
{
    // Nothing to do
}

void RsyncLogHandler::parseRsyncLogLine(const char* logLine)
{
    // Must copy logLine into a non const array because strtok will have to cut it
    char logLineToSplit[128];
    strncpy(logLineToSplit, logLine, strlen(logLine) + 1);
    logLineToSplit[strlen(logLine)+1] = 0;

    const char* token = "_";

    const char* speed = strtok(logLineToSplit, token);
    strcpy(this->speed, speed);

    const char* elapsedTime = strtok(NULL, token);
    strcpy(this->elapsedTime, elapsedTime);

    const char* currentFileNumber = strtok(NULL, token);
    strcpy(this->currentFileNumber, currentFileNumber);

    const char* remainingFiles = strtok(NULL, token);
    strcpy(this->remainingFiles, remainingFiles);
}

const char* RsyncLogHandler::getSpeed()
{
    return this->speed;
}

const char* RsyncLogHandler::getElapsedTime()
{
    return this->elapsedTime;
}

const char* RsyncLogHandler::getCurrentFileNumber()
{
    return this->currentFileNumber;
}

const char* RsyncLogHandler::getRemainingFiles()
{
    return this->remainingFiles;
}
