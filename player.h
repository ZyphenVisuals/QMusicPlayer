#ifndef PLAYER_H
#define PLAYER_H

#include <QAudioOutput>
#include <QImage>
#include <QMediaPlayer>
#include <QObject>
#include <QSettings>
#include <QUrl>

#include "playlist.h"
#include "song.h"

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(
        Song *currentSong READ currentSong WRITE setCurrentSong NOTIFY currentSongChanged FINAL)
    Q_PROPERTY(qint64 timecode READ timecode WRITE setTimecode NOTIFY timecodeChanged FINAL)
    Q_PROPERTY(bool playing READ playing WRITE setPlaying NOTIFY playingChanged FINAL)
    Q_PROPERTY(QAudioOutput *audioOutput READ getAudioOutput CONSTANT FINAL)
    Q_PROPERTY(bool loop READ loop WRITE setLoop NOTIFY loopChanged FINAL)
    Q_PROPERTY(QString order READ order WRITE setOrder NOTIFY orderChanged FINAL)
public:
    explicit Player(Playlist *playlist, QObject *parent = nullptr);

    qint64 timecode() const;
    void setTimecode(qint64 newTimecode);

    bool playing() const;
    void setPlaying(bool newPlaying);

    Song *currentSong() const;
    void setCurrentSong(Song *newCurrentSong);

    QAudioOutput *getAudioOutput() const;

    bool loop() const;
    void setLoop(bool newLoop);

    QString order() const;
    void setOrder(const QString &newOrder);

signals:
    void timecodeChanged();

    void playingChanged();

    void currentSongChanged();

    void loopChanged();

    void orderChanged();

public slots:
    void play();
    void pause();
    void next();
    void previous();
    void seek(qint64 timecode);
    void open(Song *song);
    void saveVolume();

private:
    // properties
    qint64 m_timecode;
    bool m_playing;

    // others
    QMediaPlayer *player;
    Song *m_currentSong = nullptr;
    QAudioOutput *audioOutput;
    QSettings *settings;
    bool m_loop = false;
    Playlist *playlist;
    QString m_order;
};

#endif // PLAYER_H
