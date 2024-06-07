#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QSettings>

class ThemeManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int accentColor READ accentColor WRITE setAccentColor NOTIFY accentColorChanged FINAL)
public:
    explicit ThemeManager(QObject *parent = nullptr);

    int accentColor() const;
    void setAccentColor(int newAccentColor);

signals:
    void accentColorChanged();

private:
    int m_accentColor;
    QSettings *m_settings;
};

#endif // THEMEMANAGER_H
