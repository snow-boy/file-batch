#include "Logger.h"

namespace
{
    void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
    {
        QByteArray localMsg = msg.toLocal8Bit();
        switch (type)
        {
        case QtDebugMsg:
            emit Logger::get()->logDebug(msg);
            break;
        case QtInfoMsg:
            emit Logger::get()->logInfo(msg);
            break;
        case QtWarningMsg:
            emit Logger::get()->logWarning(msg);
            break;
        case QtCriticalMsg:
            emit Logger::get()->logCritical(msg);
            break;
        case QtFatalMsg:
            emit Logger::get()->logFatal(msg);
            break;
        }
    }
}

Logger *Logger::get()
{
    static Logger s_inst;
    return &s_inst;
}

void Logger::init()
{
    qInstallMessageHandler(myMessageOutput);
}
