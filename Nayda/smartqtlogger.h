#ifndef SMARTQTLOGGER_H
#define SMARTQTLOGGER_H
#include <QDebug>
#include <QObject>
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <QTimer>
#include <QTime>

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

static const uint32_t msecloggerNextMessageTimeout = 5000;

class Logger : public QObject
{
    Q_OBJECT

private:

    QTimer* _outputController = nullptr;

private:

    static const std::vector<LoggerLevel> levels;
    LoggerLevel _currentMessageLevel = LoggerLevel::All;
    QString _initializerString;
    QString _className;
    bool _notifyCalssName = true;
    QDebug _debug = qDebug();

    bool _initializerStringAlreadyPrinted = false;

    void NewLine()
    {
        if (_outputController != nullptr)
            if (_outputController->isActive())
                _outputController->stop();

        QDebug dbg = qDebug();
        _debug.swap(dbg);
        _initializerStringAlreadyPrinted = false;
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
            _outputController->stop();
            if (_initializerStringAlreadyPrinted)
                _debug << message;
            else
            {
               _debug << QTime::currentTime().toString("hh:mm:ss.zzz") << qPrintable(_initializerString) << message;
               _initializerStringAlreadyPrinted = true;
            }
            _outputController->setInterval(msecloggerNextMessageTimeout);
            _outputController->start();
        }
        return *this;
    }

public:

    Logger& Info();
    Logger& Warning();
    Logger& Debug();
    Logger& Error();
    Logger& Essential();
    Logger& TaskCompletion();
    Logger& Observation();
    Logger& Algorithm();

    ~Logger() { }
    Logger (QObject *parent = nullptr);
    Logger (const QString& className, QObject *parent = nullptr);

};

#define PREFIX_STRINGIFY(text) #text
#define STRINGIFY(text) PREFIX_STRINGIFY(text)

#define DECLARE_NAMED_LOGGER(name) do { logger.SetLoggerName(STRINGIFY(name)); } while (0)

#endif // SMARTQTLOGGER_H
