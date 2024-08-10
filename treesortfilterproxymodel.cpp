#include "treesortfilterproxymodel.h"

TreeSortFilterProxyModel::TreeSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{}

bool TreeSortFilterProxyModel::filterAcceptsRow(int src, const QModelIndex &parent) const
{
    QModelIndex index = sourceModel()->index(src, 0, parent);

    if (sourceModel()->data(index).toString().contains(filterRegularExpression()))
    {
        return true;
    }

    for (int i = 0; i < sourceModel()->rowCount(index); ++i)
    {
        if (filterAcceptsRow(i, index))
            return true;
    }

    return false;
}
