#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QImageReader>

#include "Backend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qDebug() << QImageReader::supportedImageFormats();

    Backend *backend = new Backend(&app);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("Backend", backend);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("CarDealershipMobileApp", "Main");

    return app.exec();
}
