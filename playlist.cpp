#include "playlist.h"

Playlist::Playlist(QString title, PlayListType type, QObject *parent) : QObject{parent}
{
    this->title = title;
    this->type = type;
}
