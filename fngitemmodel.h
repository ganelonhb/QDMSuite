#ifndef FNGITEMMODEL_H
#define FNGITEMMODEL_H

#include <QAbstractItemModel>
#include <QObject>
#include <QFileInfo>
#include <QFileInfoList>
#include <QFileSystemWatcher>
#include <QDir>
#include <QStandardPaths>

class FNGItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit FNGItemModel(QObject *parent = nullptr);
    ~FNGItemModel();
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void setRootDirectory(const QString &path);

signals:
    void changed();

private slots:
    void directoryChanged(const QString &path);

private:
    struct FileNode
    {
        QString name;
        QString path;
        QList<FileNode *> children;
        FileNode *parent{nullptr};
    };

    bool directoryContainsToml(const QString &directoryPath);
    void traverseDirectory(const QString &directoryPath, FileNode *parentNode);
    FileNode *findNode(const QString &path, FileNode *parentNode) const;
    FileNode *rootNode;
    QFileSystemWatcher *fileSystemWatcher;
};

#endif // FNGITEMMODEL_H
