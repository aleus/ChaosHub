/// @author M. A. Serebrennikov

#include "Record.h"
#include "RecordsMaster.h"
#include "RecordsModel.h"
#include "Storage.h"
#include "TextNote.h"
#include "Tools.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    // Отключено qml кеширование, т.к. глючат иногда enum'ы.
    qputenv("QML_DISABLE_DISK_CACHE", "1");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:///"); // Позволяет импортировать QML в формате import Components 1.0
    auto context = engine.rootContext();

    // Регистрация классов в QML
    qRegisterMetaType<sp::Record *>("sp::Record *");
    qRegisterMetaType<sp::RecordContent *>("sp::RecordContent *");
    qRegisterMetaType<sp::TextNote *>("sp::TextNote *");

    qmlRegisterType<sp::RecordsModel>("Sp", 1, 0, "RecordsModel");
    qmlRegisterSingletonInstance("Sp", 1, 0, "TextNoteMaster", new sp::TextNoteMaster());

    // Регистрация переменных в QML
    context->setContextProperty("RecordsMaster", &RecordsMasterI);
    context->setContextProperty("Storage", &StorageI);
    context->setContextProperty("dp", sp::tools::dp());
    context->setContextProperty("mm", sp::tools::mm());

    // Загрузка QML
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    auto onObjectCreated = [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        }
    };
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, onObjectCreated, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
