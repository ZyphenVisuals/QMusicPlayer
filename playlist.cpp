#include <QDebug>

#include "playlist.h"

void Playlist::generateSortedLists()
{
    this->m_songs_album = this->m_songs;
    this->m_songs_artist = this->m_songs;

    std::stable_sort(this->m_songs_album.begin(), this->m_songs_album.end(), [](Song *a, Song *b) {
        return a->album() < b->album();
    });

    std::stable_sort(this->m_songs_artist.begin(),
                     this->m_songs_artist.end(),
                     [](Song *a, Song *b) { return a->artist() < b->artist(); });

    qDebug() << "[Playlist] Sorted songs by album and artist";
}

Playlist::Playlist(QString title, PlayListType type, QObject *parent) : QObject{parent}
{
    this->m_title = title;
    this->m_type = type;

}

QVector<Song *> Playlist::songs() const
{
    return this->m_songs;
}

QVector<Song *> Playlist::songsByAlbum() const
{
    return this->m_songs_album;
}

QVector<Song *> Playlist::songsByArtist() const
{
    return this->m_songs_artist;
}

QString Playlist::title() const
{
    return this->m_title;
}

Playlist::PlayListType Playlist::type() const
{
    return this->m_type;
}

int Playlist::count() const
{
    return m_songs.size();
}

Song *Playlist::next(Song *currentSong, QString orderBy)
{
    if (orderBy == "album") {
        for (int i = 0; i < this->m_songs_album.size(); i++) {
            if (this->m_songs_album.at(i) == currentSong) {
                if (i + 1 < this->m_songs_album.size()
                    && this->m_songs_album.at(i + 1)->album() == currentSong->album()) {
                    return this->m_songs_album.at(i + 1);
                }
            }
        }
    } else if (orderBy == "artist") {
        for (int i = 0; i < this->m_songs_artist.size(); i++) {
            if (this->m_songs_artist.at(i) == currentSong) {
                if (i + 1 < this->m_songs_artist.size()
                    && this->m_songs_artist.at(i + 1)->artist() == currentSong->artist()) {
                    return this->m_songs_artist.at(i + 1);
                }
            }
        }
    } else {
        for (int i = 0; i < this->m_songs.size(); i++) {
            if (this->m_songs.at(i) == currentSong) {
                if (i + 1 < this->m_songs.size()) {
                    return this->m_songs.at(i + 1);
                }
            }
        }
    }

    return nullptr;
}

Song *Playlist::previous(Song *currentSong, QString orderBy)
{
    if (orderBy == "album") {
        for (int i = 0; i < this->m_songs_album.size(); i++) {
            if (this->m_songs_album.at(i) == currentSong) {
                if (i - 1 >= 0 && this->m_songs_album.at(i - 1)->album() == currentSong->album()) {
                    return this->m_songs_album.at(i - 1);
                }
            }
        }
    } else if (orderBy == "artist") {
        for (int i = 0; i < this->m_songs_artist.size(); i++) {
            if (this->m_songs_artist.at(i) == currentSong) {
                if (i - 1 >= 0
                    && this->m_songs_artist.at(i - 1)->artist() == currentSong->artist()) {
                    return this->m_songs_artist.at(i - 1);
                }
            }
        }
    } else {
        for (int i = 0; i < this->m_songs.size(); i++) {
            if (this->m_songs.at(i) == currentSong) {
                if (i - 1 >= 0) {
                    return this->m_songs.at(i - 1);
                }
            }
        }
    }

    return nullptr;
}

void Playlist::addSong(Song *song)
{
    // check if song is already in playlist
    for (Song *s : this->m_songs) {
        if (s->source() == song->source()) {
            return;
        }
    }

    qDebug() << "[Playlist] Adding song" << song->title() << "to playlist" << this->title();

    QObject::connect(song, &Song::dataLoaded, this, &Playlist::songDataLoaded);

    emit this->preSongAdded();
    this->m_songs.append(song);
    emit this->postSongAdded();
}

void Playlist::songDataLoaded(QUrl source)
{
    for (int i = 0; i < this->m_songs.size(); i++) {
        if (this->m_songs.at(i)->source() == source) {
            emit this->songChanged(i);
            break;
        }
    }
    this->generateSortedLists();
}
