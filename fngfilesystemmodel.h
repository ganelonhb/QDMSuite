#ifndef FNGFILESYSTEMMODEL_H
#define FNGFILESYSTEMMODEL_H

#include <QFileSystemModel>
#include <QObject>
#include <QVariant>
#include <cpptoml/cpptoml.h>

class FNGFileSystemModel : public QFileSystemModel
{
    Q_OBJECT
public:
    explicit FNGFileSystemModel(QObject *parent = nullptr);

    void fetchMore(const QModelIndex &parent) override;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role= Qt::DisplayRole) const override;
};

#endif // FNGFILESYSTEMMODEL_H
