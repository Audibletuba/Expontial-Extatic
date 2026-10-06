#pragma once

#include "Manager.h"
#include <stdio.h>
#include <stdarg.h>

const char LOGFILE_NAME[] = "dragonfly.log";

class LogManager : public Manager
{
private:
    FILE* m_p_file;      // Log file handle
    bool m_do_flush;     // Flush file buffer after every write

    // Singeleton
    LogManager();                                 
    LogManager(const LogManager&) = delete;            
    LogManager& operator=(const LogManager&) = delete; 

public:
    ~LogManager();

    // Singleton instance getter
    static LogManager& getInstance();

    // Manager life-cycle overrides
    int startUp();
    void shutDown();

    // Buffer flushing control
    void setFlush(bool do_flush = true);

    // Primary printf-style formatted logger
    int writeLog(const char* fmt, ...);
};