#include "LogWidget.h"

#include <QDateTime>

#include "Logger.h"

LogWidget::LogWidget(QWidget *parent) : QTextEdit(parent)
{
    connect(Logger::get(), &Logger::logDebug, this, [this](const QString &msg)
            { append(QStringLiteral("[%1][debug] %2").arg(QDateTime::currentDateTime().toString(QStringLiteral("hh:mm:ss.zzz")), msg)); });
    connect(Logger::get(), &Logger::logInfo, this, [this](const QString &msg)
            { append(QStringLiteral("[%1][info] %2").arg(QDateTime::currentDateTime().toString(QStringLiteral("hh:mm:ss.zzz")), msg)); });
    connect(Logger::get(), &Logger::logWarning, this, [this](const QString &msg)
            { append(QStringLiteral("[%1][warning] %2").arg(QDateTime::currentDateTime().toString(QStringLiteral("hh:mm:ss.zzz")), msg)); });
    connect(Logger::get(), &Logger::logCritical, this, [this](const QString &msg)
            { append(QStringLiteral("[%1][critical] %2").arg(QDateTime::currentDateTime().toString(QStringLiteral("hh:mm:ss.zzz")), msg)); });
    connect(Logger::get(), &Logger::logFatal, this, [this](const QString &msg)
            { append(QStringLiteral("[%1][fatal] %2").arg(QDateTime::currentDateTime().toString(QStringLiteral("hh:mm:ss.zzz")), msg)); });
}

LogWidget::~LogWidget()
{
}