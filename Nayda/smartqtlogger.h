#ifndef SMARTQTLOGGER_H
#define SMARTQTLOGGER_H
#include <QDebug>
#include <QString>
#include <stdio.h>
#include <stdlib.h>


enum class LoggerLevel
{
    Info = 0,
    Warning,
    Debug,
    Error,
    Essential,
    TaskCompletion,
    Observation,
    Algorithm,
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

    QDebug _debug = qDebug();

    void NewLine()
    {
        QDebug dbg = qDebug();
        _debug.swap(dbg);
    }

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
        case LoggerLevel::Algorithm:
            return "Algorithm";
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
            _debug << qPrintable(_initializerString) << message;
        }
        return *this;
    }

public:

    Logger& Info()
    {
        NewLine();
        _initializerString = "[" + GetLogLevelName(LoggerLevel::Info) + "]";
        _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
        return *this;
    }

    Logger& Warning()
    {
        NewLine();
        _initializerString = "[" + GetLogLevelName(LoggerLevel::Warning) + "]";
        _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
        return *this;
    }

    Logger& Debug()
    {
        NewLine();
        _initializerString = "[" + GetLogLevelName(LoggerLevel::Debug) + "]";
        _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
        return *this;
    }

    Logger& Error()
    {
        NewLine();
        _initializerString = "[" + GetLogLevelName(LoggerLevel::Error) + "]";
        _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
        return *this;
    }

    Logger& Essential()
    {
        NewLine();
        _initializerString = "[" + GetLogLevelName(LoggerLevel::Essential) + "]";
        _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
        return *this;
    }

    Logger& TaskCompletion()
    {
        NewLine();
        _initializerString = "[" + GetLogLevelName(LoggerLevel::TaskCompletion) + "]";
        _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
        return *this;
    }

    Logger& Observation()
    {
        NewLine();
        _initializerString = "[" + GetLogLevelName(LoggerLevel::Observation) + "]";
        _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
        return *this;
    }

    Logger& Algorithm()
    {
        NewLine();
        _initializerString = "[" + GetLogLevelName(LoggerLevel::Algorithm) + "]";
        _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
        return *this;
    }

    Logger ()
    {
        QMessageLogger* logger = new QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC);
        logger->debug();
    }
    Logger (const QString& className) : _className(className) { }

};

#define PREFIX_STRINGIFY(text) #text
#define STRINGIFY(text) PREFIX_STRINGIFY(text)

#define DECLARE_NAMED_LOGGER(name) do { logger.SetLoggerName(STRINGIFY(name)); } while (0)

#endif // SMARTQTLOGGER_H
