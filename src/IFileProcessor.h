#pragma once

#include <QString>

class IFileProcessor
{
public:
    virtual ~IFileProcessor() = default;
    virtual bool replace(const QString &file, const QString &match, const QString &replace) = 0;

    static IFileProcessor *get(const QString &suffix);
};
