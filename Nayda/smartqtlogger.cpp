#include "smartqtlogger.h"
#include <QObject>
#include <QTimer>


const std::vector<LoggerLevel>Logger::levels = { LoggerLevel::All };

Logger &Logger::Info()
{
    NewLine();
    _initializerString = "[" + GetLogLevelName(LoggerLevel::Info) + "]";
    _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
    return *this;
}

Logger &Logger::Warning()
{
    NewLine();
    _initializerString = "[" + GetLogLevelName(LoggerLevel::Warning) + "]";
    _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
    return *this;
}

Logger &Logger::Debug()
{
    NewLine();
    _initializerString = "[" + GetLogLevelName(LoggerLevel::Debug) + "]";
    _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
    return *this;
}

Logger &Logger::Error()
{
    NewLine();
    _initializerString = "[" + GetLogLevelName(LoggerLevel::Error) + "]";
    _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
    return *this;
}

Logger &Logger::Essential()
{
    NewLine();
    _initializerString = "[" + GetLogLevelName(LoggerLevel::Essential) + "]";
    _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
    return *this;
}

Logger &Logger::TaskCompletion()
{
    NewLine();
    _initializerString = "[" + GetLogLevelName(LoggerLevel::TaskCompletion) + "]";
    _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
    return *this;
}

Logger &Logger::Observation()
{
    NewLine();
    _initializerString = "[" + GetLogLevelName(LoggerLevel::Observation) + "]";
    _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
    return *this;
}

Logger &Logger::Algorithm()
{
    NewLine();
    _initializerString = "[" + GetLogLevelName(LoggerLevel::Algorithm) + "]";
    _notifyCalssName ? _initializerString += " " + _className + " :: " : "GeneralNotification:: ";
    return *this;
}

Logger::Logger(QObject *parent)
{
    //Due to lack of fuction which is allow to set not-new-string in qDebug() macro or QMessageLogger
    //There should be a timer supposed to swap QDebug() since there's no other possibility to
    //call the destructor of qDebug() on which the actual printing takes place.
    _outputController = new QTimer(this);
    _outputController->setSingleShot(true);
    _outputController->setInterval(100);
    QObject::connect(_outputController, &QTimer::timeout, this, &Logger::NewLine);
}

Logger::Logger(const QString &className, QObject *parent) : _className(className)
{
    _outputController = new QTimer(this);
    _outputController->setSingleShot(true);
    _outputController->setInterval(100);
    QObject::connect(_outputController, &QTimer::timeout, this, &Logger::NewLine);
}
