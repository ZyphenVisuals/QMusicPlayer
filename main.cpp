#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStyleHints>

#include "filemanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    FileManager *fileManager = new FileManager(&app);
    qmlRegisterSingletonInstance("com.trinitystudios.FileManager", 1, 0, "FileManager", fileManager);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/PPMusicProject/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
