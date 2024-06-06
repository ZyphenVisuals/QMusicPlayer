#include <QDebug>

#include "playlist.h"

Playlist::Playlist(QString title, PlayListType type, QObject *parent) : QObject{parent}
{
    this->m_title = title;
    this->m_type = type;

    qDebug() << "[Playlist] Created playlist:" << this->title();
}

QVector<Song *> Playlist::songs() const
{
    return this->m_songs;
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
}
