#ifndef SMARTQTLOGGER_H
#define SMARTQTLOGGER_H
#include <QDebug>

enum class LoggerLevel
{
    Info,
    Warning,
    Debug,
    Error,
    Essential,
    TaskCompletion,
    Observation
};

template <typename T>
class Logger
{

};


#endif // SMARTQTLOGGER_H
