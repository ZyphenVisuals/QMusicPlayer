#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QUrl>
#include <QList>

class Playlist : public QObject
{
    Q_OBJECT
public:
    enum class PlayListType {Master, Album, Artist};

    explicit Playlist(QString title, PlayListType type, QObject *parent = nullptr);
    void addSong(QUrl songUrl);
    QUrl getSong(int index);
    int getLength();

    void print(); // debug purposes

private:
    QList<QUrl> urls;
    QString title;
    PlayListType type;
};

#endif // PLAYLIST_H
