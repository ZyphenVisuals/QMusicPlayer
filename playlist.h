#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QVector>

#include "song.h"

class Playlist : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY postSongAdded FINAL)
public:
    enum class PlayListType {Master, Album, Artist};

    explicit Playlist(QString title, PlayListType type, QObject *parent = nullptr);

    QVector<Song *> songs() const;

    QString title() const;

    PlayListType type() const;

    int count() const;

public slots:

    void addSong(Song *song);
    void songDataLoaded(QUrl source);

signals:
    void preSongAdded();
    void postSongAdded();

    void songChanged(int index);

private:
    QVector<Song *> m_songs;
    QString m_title;
    PlayListType m_type;
};

#endif // PLAYLIST_H
