/// @author M. A. Serebrennikov

#include "Record.h"
#include "RecordHelper.h"
#include "RecordMaster.h"
#include "RecordModel.h"
#include "Storage.h"
#include "TextNote.h"
#include "TextNoteMaster.h"
#include "Tools.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>

int main(int argc, char *argv[])
{
    using namespace sp;

    // Отключено qml кеширование, т.к. глючат иногда enum'ы.
    qputenv("QML_DISABLE_DISK_CACHE", "1");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:///"); // Позволяет импортировать QML в формате import Components 1.0
    auto context = engine.rootContext();

    // Тюнинг шрифтов
    QQuickWindow::setTextRenderType(QQuickWindow::NativeTextRendering);

    // Регистрация классов в QML
    qRegisterMetaType<Record *>("Record *");
    qRegisterMetaType<RecordContent *>("RecordContent *");
    qRegisterMetaType<TextNote *>("TextNote *");

    qmlRegisterType<RecordModel>("Sp", 1, 0, "RecordModel");
    qmlRegisterSingletonInstance("Sp", 1, 0, "TextNoteMaster", &TextNoteMasterI);
    qmlRegisterSingletonInstance("Sp", 1, 0, "RecordHelper", &RecordHelperI);

    // Регистрация переменных в QML
    context->setContextProperty("RecordMaster", &RecordMasterI);
    context->setContextProperty("Storage", &StorageI);
    context->setContextProperty("dp", tools::dp());
    context->setContextProperty("mm", tools::mm());

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
