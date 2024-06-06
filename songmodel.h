#ifndef SONGMODEL_H
#define SONGMODEL_H

#include <QAbstractListModel>

#include "playlist.h"

class SongModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(Playlist *playlist READ playlist WRITE setPlaylist CONSTANT FINAL)
    Q_PROPERTY(QString orderBy READ orderBy WRITE setOrderBy NOTIFY orderByChanged FINAL)

public:
    explicit SongModel(QObject *parent = nullptr);

    enum {
        TitleRole = Qt::UserRole,
        ArtistRole,
        AlbumRole,
        DurationRole,
        CoverRole,
        SourceRole,
        SongRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Playlist *playlist() const;
    void setPlaylist(Playlist *playlist);

    QString orderBy() const;
    void setOrderBy(const QString &newOrderBy);

signals:
    void orderByChanged();

private:
    Playlist *m_playlist;
    QString m_orderBy;
};

#endif // SONGMODEL_H
