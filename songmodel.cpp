#include "songmodel.h"
#include "playlist.h"

SongModel::SongModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_playlist = nullptr;
}

int SongModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !m_playlist)
        return 0;

    return m_playlist->songs().size();
}

QVariant SongModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_playlist)
        return QVariant();

    const Song *song = m_playlist->songs().at(index.row());

    switch (role) {
    case TitleRole:
        return song->title();
    case ArtistRole:
        return song->artist();
    case AlbumRole:
        return song->album();
    case DurationRole:
        return song->duration();
    case CoverRole:
        return song->coverUrl();
    case SourceRole:
        return song->source();
    }

    return QVariant();
}

QHash<int, QByteArray> SongModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[ArtistRole] = "artist";
    roles[AlbumRole] = "album";
    roles[DurationRole] = "duration";
    roles[CoverRole] = "cover";
    roles[SourceRole] = "source";
    return roles;
}

Playlist *SongModel::playlist() const
{
    return m_playlist;
}

void SongModel::setPlaylist(Playlist *playlist)
{
    this->beginResetModel();

    if (m_playlist)
        m_playlist->disconnect(this);

    m_playlist = playlist;

    if (m_playlist) {
        connect(m_playlist, &Playlist::preSongAdded, this, [=]() {
            this->beginInsertRows(QModelIndex(),
                                  m_playlist->songs().size(),
                                  m_playlist->songs().size());
        });
        connect(m_playlist, &Playlist::postSongAdded, this, [=]() { this->endInsertRows(); });
        connect(m_playlist, &Playlist::songChanged, this, [=](int index) {
            QModelIndex modelIndex = createIndex(index, 0);
            emit dataChanged(modelIndex, modelIndex);
        });
    }

    this->endResetModel();
}
