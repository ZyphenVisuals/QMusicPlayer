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
    QVector<Song *> songsByAlbum() const;
    QVector<Song *> songsByArtist() const;

    QString title() const;

    PlayListType type() const;

    int count() const;

    Song *next(Song *currentSong, QString orderBy);
    Song *previous(Song *currentSong, QString orderBy);

public slots:

    void addSong(Song *song);
    void songDataLoaded(QUrl source);

signals:
    void preSongAdded();
    void postSongAdded();

    void songChanged(int index);

private:
    QVector<Song *> m_songs;
    QVector<Song *> m_songs_album;
    QVector<Song *> m_songs_artist;
    QString m_title;
    PlayListType m_type;
    void generateSortedLists();
};

#endif // PLAYLIST_H
