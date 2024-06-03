#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);

public slots:
    void listFolderContents(QString folderUrlString);

signals:
};

#endif // FILEMANAGER_H
