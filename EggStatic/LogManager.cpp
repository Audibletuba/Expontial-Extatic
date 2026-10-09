#include "LogManager.h"

LogManager::LogManager()
{
    m_p_file = nullptr;
    m_do_flush = true;
}

LogManager::~LogManager()
{
    if (getIsRunning())
    {
        shutDown();
    }
}

// LogManager Singleton
LogManager& LogManager::getInstance()
{
    static LogManager instance;
    return instance;
}

// startUp and shutDown
int LogManager::startUp()
{
    if (getIsRunning())
    {
        return 1;
    }

    // Open dragonfly.log for writing
    if (fopen_s(&m_p_file, LOGFILE_NAME, "w") != 0)
    {
        m_p_file = nullptr;
        return 1;
    }

    // Call base Manager startup (sets isRunning = true)
    Manager::startUp();

    writeLog("LogManager StartUp.\n");
}

void LogManager::shutDown()
{
    if (!getIsRunning())
    {
        return;
    }

    writeLog("LogManager ShutDown.\n");

    if (m_p_file != nullptr)
    {
        fclose(m_p_file);
        m_p_file = nullptr;
    }

    // Call base Manager shutDown (sets isRunning = false)
    Manager::shutDown();
}

void LogManager::setFlush(bool do_flush)
{
    m_do_flush = do_flush;
}

// writeLog for variadic formatted output
int LogManager::writeLog(const char* fmt, ...)
{
    if (!getIsRunning() || m_p_file == nullptr)
    {
        return -1;
    }

    va_list args;
    va_start(args, fmt);

    int bytes_written = vfprintf(m_p_file, fmt, args);

    va_end(args);

    if (m_do_flush)
    {
        fflush(m_p_file);
    }

    return bytes_written;
}