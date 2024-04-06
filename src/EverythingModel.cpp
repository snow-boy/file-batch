#include "EverythingModel.h"

#include <QDebug>
#include <everything_sdk/Everything.h>

EverythingModel::EverythingModel(QObject *parent) : QAbstractTableModel(parent)
{
}

EverythingModel::~EverythingModel()
{
}

void EverythingModel::setFilter(const QString &filter)
{
    qInfo().noquote() << QStringLiteral("Searching for") << filter << QStringLiteral("...");

    beginResetModel();

    _filter = filter;
    Everything_SetSearchW(filter.toStdWString().c_str());
    Everything_QueryW(TRUE);

    endResetModel();

    qInfo().noquote() << QStringLiteral("Done");
}

int EverythingModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return Everything_GetNumResults();
}

int EverythingModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return 2;
}

QVariant EverythingModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
        {
            return QStringLiteral("File Name");
        }
        case 1:
        {
            return QStringLiteral("File Path");
        }
        default:
        {
            break;
        }
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant EverythingModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
    {
        return {};
    }

    if (index.column() == 0)
    {
        return QString::fromWCharArray(Everything_GetResultFileNameW(index.row()));
    }
    else if (index.column() == 1)
    {
        return QString::fromWCharArray(Everything_GetResultPathW(index.row()));
    }

    return QVariant();
}
