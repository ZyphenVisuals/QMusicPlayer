#include "song.h"
#include <QDebug>
#include <QMediaMetaData>
#include <QUrl>

Song::Song(QUrl file, QObject *parent)
    : QObject{parent}
{
    // set the source
    this->setSource(file);

    // set the default data
    this->setAlbum("Loading...");
    this->setArtist("Loading...");
    this->setTitle("Loading...");
    this->setDuration(0);

    // load the default cover
    QImage cover;
    if (cover.load(":/images/default_cover.png")) {
        this->setCover(cover);
    } else {
        qWarning() << "[Song] Could not load default cover image!";
    }

    // start loading the song data
    this->loadData();
}

void Song::loadData()
{
    // create a temporary media player
    m_tempMediaPlayer = new QMediaPlayer(this);
    // load the song
    m_tempMediaPlayer->setSource(m_source);
    // wait for the song to load
    connect(
        m_tempMediaPlayer,
        &QMediaPlayer::mediaStatusChanged,
        this,
        [=](QMediaPlayer::MediaStatus status) {
            if (status == QMediaPlayer::LoadedMedia) {
                QList<QMediaMetaData::Key> available = m_tempMediaPlayer->metaData().keys();

                // set the title
                if (available.contains(QMediaMetaData::Title)) {
                    this->setTitle(
                        m_tempMediaPlayer->metaData().value(QMediaMetaData::Title).toString());
                } else {
                    this->setTitle("Unknown title");
                }

                // set the artist
                if (available.contains(QMediaMetaData::Author)) {
                    this->setArtist(
                        m_tempMediaPlayer->metaData().value(QMediaMetaData::Author).toString());
                } else if (available.contains(QMediaMetaData::AlbumArtist)) {
                    this->setArtist(
                        m_tempMediaPlayer->metaData().value(QMediaMetaData::AlbumArtist).toString());
                } else {
                    this->setArtist("Unknown artist");
                }

                // set the album
                if (available.contains(QMediaMetaData::AlbumTitle)) {
                    this->setAlbum(
                        m_tempMediaPlayer->metaData().value(QMediaMetaData::AlbumTitle).toString());
                } else {
                    this->setAlbum("Unknown album");
                }

                // set the duration
                this->setDuration(m_tempMediaPlayer->duration());

                // set the cover
                if (available.contains(QMediaMetaData::CoverArtImage)) {
                    this->setCover(qvariant_cast<QImage>(
                        m_tempMediaPlayer->metaData().value(QMediaMetaData::CoverArtImage)));
                } else if (available.contains(QMediaMetaData::ThumbnailImage)) {
                    this->setCover(qvariant_cast<QImage>(
                        m_tempMediaPlayer->metaData().value(QMediaMetaData::ThumbnailImage)));
                } else {
                    qWarning() << "[Song] No cover found for: " << m_source.fileName();
                }

                // delete the temporary media player
                m_tempMediaPlayer->deleteLater();

                // debug print
                qDebug() << "[Song] Loaded song:" << m_source.fileName() << m_title << m_artist;
            }
        });
}

QString Song::title() const
{
    return m_title;
}

void Song::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();
}

QString Song::artist() const
{
    return m_artist;
}

void Song::setArtist(const QString &newArtist)
{
    if (m_artist == newArtist)
        return;
    m_artist = newArtist;
    emit artistChanged();
}

QString Song::album() const
{
    return m_album;
}

void Song::setAlbum(const QString &newAlbum)
{
    if (m_album == newAlbum)
        return;
    m_album = newAlbum;
    emit albumChanged();
}

qint64 Song::duration() const
{
    return m_duration;
}

void Song::setDuration(qint64 newDuration)
{
    if (m_duration == newDuration)
        return;
    m_duration = newDuration;
    emit durationChanged();
}

QImage Song::cover() const
{
    return m_cover;
}

void Song::setCover(const QImage &newCover)
{
    if (m_cover == newCover)
        return;
    m_cover = newCover;
    emit coverChanged();
}

QUrl Song::source() const
{
    return m_source;
}

void Song::setSource(const QUrl &newSource)
{
    if (m_source == newSource)
        return;
    m_source = newSource;
    emit sourceChanged();
}
