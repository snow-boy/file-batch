#pragma once
#include <QTextEdit>

class LogWidget : public QTextEdit
{
    Q_OBJECT
public:
    LogWidget(QWidget *parent);
    ~LogWidget();
};
