#ifndef FNGITEMMODEL_H
#define FNGITEMMODEL_H

#include <QAbstractItemModel>
#include <QObject>
#include <QFileInfo>
#include <QFileInfoList>
#include <QFileSystemWatcher>
#include <QDir>
#include <QStandardPaths>

#include <cpptoml/cpptoml.h>
#include <fstream>


struct FileNode
{
    QString name;
    QString path;
    QList<FileNode *> children;
    FileNode *parent{nullptr};
};

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

private slots:
    void directoryChanged(const QString &path);

private:
    bool directoryContainsToml(const QString &directoryPath);
    void traverseDirectory(const QString &directoryPath, FileNode *parentNode);
    FileNode *findNode(const QString &path, FileNode *parentNode) const;
    FileNode *rootNode;
    QFileSystemWatcher *fileSystemWatcher;

    bool validateQomlFile(const QString &filePath);
};

#endif // FNGITEMMODEL_H
