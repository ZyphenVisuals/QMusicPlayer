#ifndef SONG_H
#define SONG_H

#include <QImage>
#include <QMediaPlayer>
#include <QObject>
#include <QUrl>

class Song : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(QString artist READ artist WRITE setArtist NOTIFY artistChanged FINAL)
    Q_PROPERTY(QString album READ album WRITE setAlbum NOTIFY albumChanged FINAL)
    Q_PROPERTY(qint64 duration READ duration WRITE setDuration NOTIFY durationChanged FINAL)
    Q_PROPERTY(QImage cover READ cover WRITE setCover NOTIFY coverChanged FINAL)
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged FINAL)
    Q_PROPERTY(QUrl coverUrl READ coverUrl WRITE setCoverUrl NOTIFY coverUrlChanged FINAL)
public:
    explicit Song(QUrl file, QObject *parent = nullptr);

    QString title() const;
    void setTitle(const QString &newTitle);

    QString artist() const;
    void setArtist(const QString &newArtist);

    QString album() const;
    void setAlbum(const QString &newAlbum);

    qint64 duration() const;
    void setDuration(qint64 newDuration);

    QImage cover() const;
    void setCover(const QImage &newCover);

    QUrl source() const;
    void setSource(const QUrl &newSource);

    QUrl coverUrl() const;

    void setCoverUrl(const QUrl &newCoverUrl);

signals:
    void titleChanged();

    void artistChanged();

    void albumChanged();

    void durationChanged();

    void coverChanged();

    void sourceChanged();

    void dataLoaded(QUrl source);

    void coverUrlChanged();

private:
    QString m_title;
    QString m_artist;
    QString m_album;
    qint64 m_duration;
    QImage m_cover;
    QUrl m_source;
    QUrl m_coverUrl;

    QMediaPlayer *m_tempMediaPlayer;

    void loadData();
    void loadCover();
};

#endif // SONG_H
