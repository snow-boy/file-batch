#include "SearchWidget.h"

#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QTimer>

SearchWidget::SearchWidget(QWidget *parent) : QWidget(parent)
{
    auto l = new QGridLayout(this);
    {
        auto timer = new QTimer(this);
        timer->setSingleShot(true);
        timer->setInterval(1000);

        l->addWidget(new QLabel("Filter:"), 0, 0);
        _filterEdit = new QLineEdit(this);

        connect(timer, &QTimer::timeout, this, [this]()
                { emit filterChanged(_filterEdit->text()); });

        connect(_filterEdit, &QLineEdit::textChanged, timer, [this, timer]
                { timer->start(); });

        l->addWidget(_filterEdit, 0, 1);
    }

    l->addWidget(new QLabel(), 1, 1);

    {
        l->addWidget(new QLabel("Match:"), 2, 0);
        _fileMatchEdit = new QLineEdit(this);
        l->addWidget(_fileMatchEdit, 2, 1);

        l->addWidget(new QLabel("Replace:"), 3, 0);
        _fileReplaceEdit = new QLineEdit(this);
        l->addWidget(_fileReplaceEdit, 3, 1);

        auto replaceButton = new QPushButton("Rename Files", this);
        l->addWidget(replaceButton, 4, 1);
        connect(replaceButton, &QPushButton::clicked, this, &SearchWidget::doRenameFiles);
    }

    l->addWidget(new QLabel(), 5, 1);

    {
        l->addWidget(new QLabel("Match:"), 6, 0);
        _textMatchEdit = new QLineEdit(this);
        l->addWidget(_textMatchEdit, 6, 1);

        l->addWidget(new QLabel("Replace:"), 7, 0);
        _textReplaceEdit = new QLineEdit(this);
        l->addWidget(_textReplaceEdit, 7, 1);

        auto replaceButton = new QPushButton("Replace Text", this);
        l->addWidget(replaceButton, 8, 1);
        connect(replaceButton, &QPushButton::clicked, this, &SearchWidget::doRenameFiles);
    }

    l->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding), 9, 0);
}

SearchWidget::~SearchWidget()
{
}