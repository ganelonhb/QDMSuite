#include "fngfilesystemmodel.h"

FNGFileSystemModel::FNGFileSystemModel(QObject *parent)
    : QFileSystemModel{parent}
{}

void FNGFileSystemModel::fetchMore(const QModelIndex &parent)
{
    if (!parent.isValid())
        return;

    QFileSystemModel::fetchMore(parent);

    int rowCount = this->rowCount(parent);
    for (int i = rowCount - 1; i >= 0; --i) {
        QModelIndex index = this->index(i, 0, parent);
        QString filePath = this->filePath(index);
        QFileInfo fileInfo(filePath);
        if (fileInfo.isFile() && !fileInfo.fileName().endsWith(".toml")) {
            this->removeRow(i, parent);
        }
    }
}

bool FNGFileSystemModel::hasChildren(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return true;

    QString parentPath = this->filePath(parent);
    QDir dir(parentPath);
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    dir.setNameFilters(QStringList() << "*.toml");

    return !dir.entryList().isEmpty();
}

QVariant FNGFileSystemModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        QString filePath = this->filePath(index);
        QFileInfo fileInfo(filePath);
        if (fileInfo.isFile() && fileInfo.fileName().endsWith(".toml")) {
            try {
                auto config = cpptoml::parse_file(filePath.toStdString());
                if (config->contains("name")) {
                    auto name = config->get_as<std::string>("name");
                    if (name) {
                        return QString::fromStdString(*name);
                    }
                }
            } catch (const cpptoml::parse_exception &e) {
                qDebug() << "Failed to parse toml file:" << e.what();
            }
        }
    }
    return QFileSystemModel::data(index, role);
}
