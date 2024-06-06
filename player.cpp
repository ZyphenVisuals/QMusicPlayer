#include "player.h"

#include <QAudioOutput>

Player::Player(QAudioOutput *output, QObject *parent)
    : QObject{parent}
{
    this->player = new QMediaPlayer(this);
    this->player->setAudioOutput(output);
}

void Player::open(Song *song)
{
    this->setTimecode(0);
    this->setPlaying(false);
    this->setCurrentSong(song);
    this->player->setSource(song->source());
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

void Player::next() {}

void Player::previous() {}

void Player::seek(qint64 timecode) {}

qint64 Player::timecode() const
{
    return m_timecode;
}

void Player::setTimecode(qint64 newTimecode)
{
    if (m_timecode == newTimecode)
        return;
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
