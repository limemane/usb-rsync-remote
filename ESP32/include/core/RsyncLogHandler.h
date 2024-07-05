class RsyncLogHandler {
    public:
        RsyncLogHandler();
        void parseRsyncLogLine(const char* logLine);
        const char* getSpeed();
        const char* getElapsedTime();
        const char* getCurrentFileNumber();
        const char* getRemainingFiles();

    private:
        char speed[32];
        char elapsedTime[32];
        char currentFileNumber[32];
        char remainingFiles[32];
};