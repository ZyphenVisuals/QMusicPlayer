#include "thememanager.h"

#include <QSettings>

ThemeManager::ThemeManager(QObject *parent)
    : QObject{parent}
{
    this->m_settings = new QSettings{"Team CEX", "QMusicPlayer"};
    if (this->m_settings->contains("accentColor"))
        this->m_accentColor = this->m_settings->value("accentColor").toInt();
    else {
        this->m_accentColor = -1;
    }
}

int ThemeManager::accentColor() const
{
    return m_accentColor;
}

void ThemeManager::setAccentColor(int newAccentColor)
{
    if (m_accentColor == newAccentColor)
        return;
    m_accentColor = newAccentColor;
    m_settings->setValue("accentColor", m_accentColor);
    emit accentColorChanged();
}
