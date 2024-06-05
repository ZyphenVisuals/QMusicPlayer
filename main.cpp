#include <QDebug>
#include <QGuiApplication>
#include <QMetaType>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QStyleHints>

#include "filemanager.h"
#include "folderlistmodel.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<QList<QUrl>>("QList<QUrl>");

    QGuiApplication app(argc, argv);

    QSettings settings("Team CEX", "QMusicPlayer");
    settings.setValue("version", "1.0");
    qDebug() << "Using settings file:" << settings.fileName();

    FileManager *fileManager = new FileManager(&app);

    qmlRegisterSingletonInstance("com.teamcex.FileManager", 1, 0, "FileManager", fileManager);

    qmlRegisterType<FolderListModel>("com.teamcex.FolderListModel", 1, 0, "FolderListModel");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/PPMusicProject/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    // quit signal
    QObject::connect(&engine, &QQmlApplicationEngine::quit, &QGuiApplication::quit);

    return app.exec();
}
