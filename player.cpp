#include "player.h"

#include <QAudioOutput>
#include <QDebug>
#include <QSettings>

Player::Player(Playlist *playlist, QObject *parent)
    : QObject{parent}
{
    this->player = new QMediaPlayer(this);
    this->setPlaying(false);
    this->audioOutput = new QAudioOutput(this);
    this->settings = new QSettings("Team CEX", "QMusicPlayer", this);
    this->playlist = playlist;

    this->player->setAudioOutput(this->audioOutput);
    if (this->settings->contains("volume")) {
        qDebug() << "[Player] Loading volume:" << this->settings->value("volume").toFloat();
        this->audioOutput->setVolume(this->settings->value("volume").toFloat());
    } else {
        this->audioOutput->setVolume(0.5);
    }

    connect(this->player, &QMediaPlayer::positionChanged, this, [=](qint64 position) {
        this->setTimecode(position);
    });

    connect(this->player,
            &QMediaPlayer::mediaStatusChanged,
            this,
            [=](QMediaPlayer::MediaStatus state) {
                if (state == QMediaPlayer::EndOfMedia) {
                    this->setPlaying(false);
                    this->next();
                }
            });
}

void Player::open(Song *song)
{
    this->setTimecode(0);
    this->setPlaying(false);
    this->setCurrentSong(song);
    this->player->setSource(song->source());
    this->play();
}

void Player::saveVolume()
{
    qDebug() << "[Player] Saving volume:" << this->audioOutput->volume();
    this->settings->setValue("volume", this->audioOutput->volume());
}

QAudioOutput *Player::getAudioOutput() const
{
    return audioOutput;
}

void Player::play()
{
    if (this->currentSong() == nullptr || this->playing() == true)
        return;
    qDebug() << "[Player] Playing song:" << this->currentSong()->title();
    this->player->play();
    this->setPlaying(true);
}

void Player::pause()
{
    if (this->playing() == false || this->currentSong() == nullptr)
        return;
    qDebug() << "[Player] Pausing song:" << this->currentSong()->title();
    this->player->pause();
    this->setPlaying(false);
}

void Player::next()
{
    if (this->currentSong() == nullptr)
        return;

    if (this->loop()) {
        this->player->setPosition(0);
        this->play();
        return;
    }

    Song *nextSong = this->playlist->next(this->currentSong());

    if (nextSong != nullptr) {
        this->open(nextSong);
    }

    this->player->setPosition(0);
    this->pause();
}

void Player::previous()
{
    if (this->currentSong() == nullptr)
        return;

    if (this->loop() || this->timecode() > 10000) {
        this->player->setPosition(0);
        this->play();
        return;
    }

    Song *previousSong = this->playlist->previous(this->currentSong());

    if (previousSong != nullptr) {
        this->open(previousSong);
    }

    this->player->setPosition(0);
    this->play();
}

void Player::seek(qint64 timecode) {}

qint64 Player::timecode() const
{
    return m_timecode;
}

void Player::setTimecode(qint64 newTimecode)
{
    if (m_timecode == newTimecode)
        return;

    if (newTimecode - m_timecode > 1000 || m_timecode - newTimecode > 1000) {
        this->player->setPosition(newTimecode);
    }

    m_timecode = newTimecode;

    emit timecodeChanged();
}

bool Player::playing() const
{
    return m_playing;
}

void Player::setPlaying(bool newPlaying)
{
    if (m_playing == newPlaying)
        return;
    m_playing = newPlaying;
    emit playingChanged();
}

Song *Player::currentSong() const
{
    return m_currentSong;
}

void Player::setCurrentSong(Song *newCurrentSong)
{
    if (m_currentSong == newCurrentSong)
        return;
    m_currentSong = newCurrentSong;
    emit currentSongChanged();
}

bool Player::loop() const
{
    return m_loop;
}

void Player::setLoop(bool newLoop)
{
    if (m_loop == newLoop)
        return;
    m_loop = newLoop;
    emit loopChanged();
}
