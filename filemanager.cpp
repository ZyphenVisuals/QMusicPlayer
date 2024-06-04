#include "filemanager.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QUrl>

FileManager::FileManager(QObject *parent)
    : QObject{parent}
{}

void FileManager::scanFolderContents(QString folderUrlString)
{
    // parse URL
    QUrl folderUrl(folderUrlString);
    qDebug() << "Scanning folder: " << folderUrl.path();

    // open directory and filter for audio files
    QDir dir(folderUrl.path());
    dir.setNameFilters( QStringList() << "*.mp3" << "*.wav" << "*.ogg" << "*.flac");

    for (const QFileInfo &file : dir.entryInfoList(QDir::Files))
    {
        qDebug() << file.absoluteFilePath();
    }

    return;
}
