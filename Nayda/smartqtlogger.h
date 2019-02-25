#ifndef SMARTQTLOGGER_H
#define SMARTQTLOGGER_H
#include <QDebug>
#include <QString>



enum class LoggerLevel
{
    Info = 0,
    Warning,
    Debug,
    Error,
    Essential,
    TaskCompletion,
    Observation,
    All
};

static const LoggerLevel logLevel = LoggerLevel::All;

class Logger
{
private:

    static const std::vector<LoggerLevel> levels;
    LoggerLevel _currentMessageLevel = LoggerLevel::All;
    QString _initializerString;
    QString _className;
    bool _notifyCalssName = true;

private:

    QString GetLogLevelName(LoggerLevel type)
    {
        switch (type)
        {
        case LoggerLevel::Info:
            return "Info";
        case LoggerLevel::Warning:
            return "Warning";
        case LoggerLevel::Debug:
            return "Debug";
        case LoggerLevel::Error:
            return "Error";
        case LoggerLevel::Essential:
            return "Essential";
        case LoggerLevel::TaskCompletion:
            return "TaskCompletion";
        case LoggerLevel::Observation:
            return "Observation";
        case LoggerLevel::All:
            return "All";
        }
        return "Error Logger Name!";
    }

public:

    void SetLoggerName(const QString& className) { _className = className; }

public:

    template <typename T>
    Logger& operator<< (const T& message)
    {
        if (std::find(levels.begin(), levels.end(), _currentMessageLevel) != levels.end() )
        {
            qDebug() << qPrintable(_initializerString) << message;
        }
        return *this;
    }

public:

    Logger& Info()
    {
        _initializerString = "[" + GetLogLevelName(LoggerLevel::Info) + "]";
        _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
        return *this;
    }

    Logger () { }
    Logger (const QString& className) : _className(className) { }

};

#define PREFIX_STRINGIFY(text) #text
#define STRINGIFY(text) PREFIX_STRINGIFY(text)

#define DECLARE_NAMED_LOGGER(name) do { logger.SetLoggerName(STRINGIFY(name)); } while (0)

#endif // SMARTQTLOGGER_H
