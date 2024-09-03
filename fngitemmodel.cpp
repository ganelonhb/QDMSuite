#include "fngitemmodel.h"

FNGItemModel::FNGItemModel(QObject *parent)
    : QAbstractItemModel{parent}
    , rootNode(new FileNode{"Root", "", {}, nullptr})
{
    fileSystemWatcher = new QFileSystemWatcher(this);

    connect(fileSystemWatcher, &QFileSystemWatcher::directoryChanged, this, &FNGItemModel::directoryChanged);
}

FNGItemModel::~FNGItemModel()
{
    delete rootNode;
}

QModelIndex FNGItemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    FileNode *newParent;
    if (!parent.isValid())
        newParent = rootNode;
    else
        newParent = static_cast<FileNode *>(parent.internalPointer());

    FileNode *childNode = newParent->children.at(row);
    if (childNode)
        return createIndex(row, column, childNode);
    else
        return QModelIndex();
}

QModelIndex FNGItemModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    FileNode *childNode = static_cast<FileNode *>(index.internalPointer());
    FileNode *parentN = childNode->parent;

    if (parentN == rootNode)
        return QModelIndex();

    return createIndex(parentN->children.indexOf(childNode), 0, parentN);
}

int FNGItemModel::rowCount(const QModelIndex &parent) const
{
    FileNode * parentNode;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentNode = rootNode;
    else
        parentNode = static_cast<FileNode *>(parent.internalPointer());

    return parentNode->children.count();
}

int FNGItemModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant FNGItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    FileNode *node = static_cast<FileNode *>(index.internalPointer());

    if (role == Qt::DisplayRole)
        return node->name;

    return QVariant();
}

QVariant FNGItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0:
            return QString("Name Generators");
        default:
            return QVariant();
        }
    }

    return QVariant();
}

void FNGItemModel::setRootDirectory(const QString &path)
{
    traverseDirectory(path, rootNode);
    fileSystemWatcher->addPath(path);
}

void FNGItemModel::directoryChanged(const QString &path)
{
    beginResetModel();
    fileSystemWatcher->removePaths(fileSystemWatcher->directories());

    rootNode->children.clear();
    traverseDirectory(path, rootNode);
    fileSystemWatcher->addPath(path);
    endResetModel();
}

bool FNGItemModel::directoryContainsToml(const QString &directoryPath) {
    QDir dir(directoryPath);
    QFileInfoList entries = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::AllDirs, QDir::Name);

    foreach (const QFileInfo &entry , entries)
    {
        if (entry.isDir())
        {
            if (directoryContainsToml(entry.filePath()))
                return true;
        } else if (entry.isFile() && entry.suffix() == "qoml")
            return true;
    }
    return false;
}

void FNGItemModel::traverseDirectory(const QString &directoryPath, FileNode *parentNode)
{
    QDir dir(directoryPath);
    QFileInfoList entries = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

    QStringList watchedPaths = fileSystemWatcher->directories();

    foreach (const QFileInfo &entry, entries)
    {
        if (entry.isDir())
        {
            if (directoryContainsToml(entry.filePath()))
            {
                QDir subDir(entry.filePath());
                QFileInfoList files = subDir.entryInfoList(QStringList() << "*.qoml", QDir::Files);
                bool valid = true;

                foreach (const QFileInfo &file, files)
                {
                    if (!validateQomlFile(file.filePath()))
                    {
                        valid = false;
                        break;
                    }
                }

                if (valid)
                {
                    FileNode *node = new FileNode{entry.fileName(), entry.filePath(), {}, parentNode};
                    parentNode->children.append(node);
                    traverseDirectory(entry.filePath(), node);
                    if (!watchedPaths.contains(entry.filePath()))
                    {
                        fileSystemWatcher->addPath(entry.filePath());
                    }
                }
            }
        }
    }

    foreach (const QString &path, watchedPaths)
    {
        if (!QDir(path).exists())
        {
            fileSystemWatcher->removePath(path);
        }
    }
}



FileNode* FNGItemModel::findNode(const QString &path, FileNode *parentNode) const {

    foreach (FileNode *node , parentNode->children)
    {
        if (node->path == path)
            return node;
        if (node->children.count() > 0)
        {
            FileNode *childNode = findNode(path, node);
            if (childNode)
                return childNode;
        }
    }
    return nullptr;
}


bool FNGItemModel::validateQomlFile(const QString &filePath)
{
    try
    {
        std::shared_ptr<cpptoml::table> config =
            cpptoml::parse_file(filePath.toStdString());

        if (config->contains("name") && config->contains("script"))
            return true;

    }
    catch (const cpptoml::parse_exception &ex)
    {
        return false;
    }

    return false;
}
