#ifndef TREESORTFILTERPROXYMODEL_H
#define TREESORTFILTERPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>

class TreeSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TreeSortFilterProxyModel(QObject *parent = nullptr);

protected:
    bool filterAcceptsRow(int src, const QModelIndex &parent) const override;
};

#endif // TREESORTFILTERPROXYMODEL_H
