#pragma once

#include <QAbstractTableModel>

class EverythingModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    EverythingModel(QObject *parent = nullptr);
    ~EverythingModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void setFilter(const QString &filter);

private:
    QString _filter;
};
