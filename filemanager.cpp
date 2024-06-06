#include "filemanager.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QUrl>
#include <QVariant>

#include "song.h"

FileManager::FileManager(QObject *parent)
    : QObject{parent}
{
    this->settings = new QSettings("Team CEX", "QMusicPlayer", this);
    this->m_folders = settings->value("folders").value<QList<QUrl>>();
}

void FileManager::addFolder(QUrl folder)
{
    if (this->folders().contains(folder)) {
        qDebug() << "[FileManager] Folder already added:" << folder.toLocalFile();
        return;
    }
    qDebug() << "[FileManager] Adding folder:" << folder.toLocalFile();
    QList<QUrl> folders = this->folders();
    folders.append(folder);
    setFolders(folders);
    scanFolderContents(folder);
}

void FileManager::removeFolder(QUrl folder)
{
    qDebug() << "[FileManager] Removing folder:" << folder.toLocalFile();
    QList<QUrl> folders = this->folders();
    folders.removeAll(folder);
    setFolders(folders);
}

void FileManager::scanFolderContents(QUrl folderUrl)
{
    qDebug() << "[FileManager] Scanning folder:" << folderUrl.toLocalFile();

    // open directory
    QDir dir(folderUrl.toLocalFile());
    // set filters
    dir.setNameFilters( QStringList() << "*.mp3" << "*.wav" << "*.ogg" << "*.flac");
    // loop through all files matching the filters
    for (const QFileInfo &file : dir.entryInfoList(QDir::Files))
    {
        qDebug() << "[FileManager] Found file:" << file.fileName();
        Song *song = new Song(QUrl::fromLocalFile(file.absoluteFilePath()), this);
        emit this->newFile(song);
    }

    qDebug() << "[FileManager] Scanning finished.\n";

    return;
}

QList<QUrl> FileManager::folders() const
{
    return m_folders;
}

void FileManager::setFolders(const QList<QUrl> &newFolders)
{
    if (m_folders == newFolders)
        return;
    m_folders = newFolders;
    QVariant folders = QVariant::fromValue(m_folders);
    settings->setValue("folders", folders);
    emit foldersChanged();
}

void FileManager::scanFolders()
{
    for (const QUrl &folder : m_folders) {
        scanFolderContents(folder);
    }
}

void FileManager::openFile(QUrl songUrl)
{
    Song *song = new Song(songUrl, this);
    emit this->playSong(song);
}
