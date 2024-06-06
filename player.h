#ifndef PLAYER_H
#define PLAYER_H

#include <QAudioOutput>
#include <QImage>
#include <QMediaPlayer>
#include <QObject>
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
public:
    explicit Player(QAudioOutput *output, QObject *parent = nullptr);

    qint64 timecode() const;
    void setTimecode(qint64 newTimecode);

    bool playing() const;
    void setPlaying(bool newPlaying);

    Song *currentSong() const;
    void setCurrentSong(Song *newCurrentSong);

signals:
    void timecodeChanged();

    void playingChanged();

    void currentSongChanged();

public slots:
    void play();
    void pause();
    void next();
    void previous();
    void seek(qint64 timecode);
    void open(Song *song);

private:
    // properties
    qint64 m_timecode;
    bool m_playing;

    // others
    QMediaPlayer *player;
    Song *m_currentSong = nullptr;
};

#endif // PLAYER_H
