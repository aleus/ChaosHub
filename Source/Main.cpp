/// @author M. A. Serebrennikov
#include "Clipboard.h"
#include "Colors.h"
#include "Record.h"
#include "RecordMaster.h"
#include "RecordModel.h"
#include "Storage.h"
#include "TextEditHelper.h"
#include "TextNote.h"
#include "TextNoteMaster.h"
#include "Tools.h"

#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    using namespace sp;

    // Отключено qml кеширование, т.к. глючат иногда enum'ы.
    qputenv("QML_DISABLE_DISK_CACHE", "1");

    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:///"); // Позволяет импортировать QML в формате import Components 1.0
    auto context = engine.rootContext();

    // Тюнинг шрифтов
    // QQuickWindow::setTextRenderType(QQuickWindow::NativeTextRendering);
    QFontDatabase::addApplicationFont(":/Roboto-Black.ttf");
    QFontDatabase::addApplicationFont(":/Roboto-BlackItalic.ttf");
    QFontDatabase::addApplicationFont(":/Roboto-Bold.ttf");
    QFontDatabase::addApplicationFont(":/Roboto-BoldItalic.ttf");
    QFontDatabase::addApplicationFont(":/Roboto-Italic.ttf");
    QFontDatabase::addApplicationFont(":/Roboto-Light.ttf");
    QFontDatabase::addApplicationFont(":/Roboto-LightItalic.ttf");
    QFontDatabase::addApplicationFont(":/Roboto-Medium.ttf");
    QFontDatabase::addApplicationFont(":/Roboto-MediumItalic.ttf");
    QFontDatabase::addApplicationFont(":/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/Roboto-Thin.ttf");
    QFontDatabase::addApplicationFont(":/Roboto-ThinItalic.ttf");

    app.setFont(QFont("Roboto"));

    // Debug!!!
    StorageI.openDb(QStringLiteral("Notes.db"));
    StorageI.prepareStorage();

    // Регистрация классов в QML
    qRegisterMetaType<Record *>("Record *");
    qRegisterMetaType<RecordContent *>("RecordContent *");
    qRegisterMetaType<TextNote *>("TextNote *");

    qmlRegisterType<RecordModel>("Sp", 1, 0, "RecordModel");
    qmlRegisterType<TextEditHelper>("Sp", 1, 0, "TextEditHelper");

    // Синглетоны
    context->setContextProperty("TextNoteMaster", &TextNoteMasterI);
    context->setContextProperty("Colors", &ColorsI);
    context->setContextProperty("Clipboard", &ClipboardI);
    context->setContextProperty("RecordMaster", &RecordMasterI);
    context->setContextProperty("Storage", &StorageI);
    context->setContextProperty("dp", tools::dp());
    context->setContextProperty("mm", tools::mm());

    // Загрузка QML
    const QUrl url(QStringLiteral("qrc:/Root.qml"));

    auto onObjectCreated = [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        }
    };
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, onObjectCreated, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
