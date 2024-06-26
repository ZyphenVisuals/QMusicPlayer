#include <QAudioOutput>
#include <QDebug>
#include <QGuiApplication>
#include <QIcon>
#include <QMetaType>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QStyleHints>
#include <QSurfaceFormat>

#include "filemanager.h"
#include "player.h"
#include "playlist.h"
#include "songmodel.h"
#include "thememanager.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<QList<QUrl>>("QList<QUrl>");

    QSurfaceFormat format;
    format.setSamples(8);
    QSurfaceFormat::setDefaultFormat(format);

    QGuiApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/static/QMP.png"));

    QSettings settings("Team CEX", "QMusicPlayer");
    settings.setValue("version", "1.0");
    qDebug() << "Using settings file:" << settings.fileName();

    Playlist *playlist = new Playlist("Master", Playlist::PlayListType::Master, &app);
    Player *player = new Player(playlist, &app);
    FileManager *fileManager = new FileManager(&app);
    ThemeManager *themeManager = new ThemeManager(&app);

    QObject::connect(fileManager, &FileManager::newFile, playlist, &Playlist::addSong);
    QObject::connect(fileManager, &FileManager::playSong, player, &Player::open);

    qmlRegisterType<SongModel>("com.teamcex.SongModel", 1, 0, "SongModel");

    qmlRegisterSingletonInstance("com.teamcex.FileManager", 1, 0, "FileManager", fileManager);
    qmlRegisterSingletonInstance("com.teamcex.Player", 1, 0, "Player", player);
    qmlRegisterSingletonInstance("com.teamcex.Playlist", 1, 0, "Playlist", playlist);
    qmlRegisterSingletonInstance("com.teamcex.ThemeManager", 1, 0, "ThemeManager", themeManager);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/PPMusicProject/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    QObject::connect(&engine, &QQmlApplicationEngine::quit, &QGuiApplication::quit);

    fileManager->scanFolders();

    return app.exec();
}
