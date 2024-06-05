#include "folderlistmodel.h"

#include <QDebug>
#include <QSettings>

FolderListModel::FolderListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    this->settings = new QSettings("Team CEX", "QMusicPlayer");
}

int FolderListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    int size = settings->beginReadArray("folders");
    settings->endArray();
    return size;
}

QVariant FolderListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    settings->sync();
    settings->beginReadArray("folders");
    settings->setArrayIndex(index.row());
    QVariant value(settings->value("path"));
    settings->endArray();
    return value;
}

QHash<int, QByteArray> FolderListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PathRole] = "path";
    return roles;
}
