#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QSettings>
#include <QUrl>

class FileManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QUrl> folders READ folders WRITE setFolders NOTIFY foldersChanged FINAL)
public:
    explicit FileManager(QObject *parent = nullptr);

    QList<QUrl> folders() const;
    void setFolders(const QList<QUrl> &newFolders);

public slots:
    void addFolder(QUrl folder);
    void removeFolder(QUrl folder);

signals:
    void onNewFile(QUrl file);

    void foldersChanged();

private:
    void scanFolderContents(QUrl folderUrlString);
    QSettings *settings;
    QList<QUrl> m_folders;
};

#endif // FILEMANAGER_H
