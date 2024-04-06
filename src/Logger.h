#pragma once

#include <QObject>

class Logger : public QObject
{
    Q_OBJECT
public:
    static Logger *get();

    static void init();

signals:
    void logDebug(const QString &msg);
    void logInfo(const QString &msg);
    void logWarning(const QString &msg);
    void logCritical(const QString &msg);
    void logFatal(const QString &msg);
};
