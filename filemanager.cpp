#include "filemanager.h"
#include <QDebug>

FileManager::FileManager(QObject *parent)
    : QObject{parent}
{}

void FileManager::listFolderContents(QString folderUrlString)
{
    qDebug() << folderUrlString;
    return;
}
