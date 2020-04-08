QT += quick quickcontrols2 widgets network multimedia svg xml

CONFIG += c++17

INCLUDEPATH += \
    Source \

HEADERS += \ \
    Source/Clipboard.h \
    Source/Colors.h \
    Source/Defer.h \
    Source/PointersTypedef.h \
    Source/Record.h \
    Source/RecordContent.h \
    Source/RecordMaster.h \
    Source/RecordModel.h \
    Source/Storage.h \
    Source/Tag.h \
    Source/TagMaster.h \
    Source/TagModel.h \
    Source/TextEditHelper.h \
    Source/TextNote.h \
    Source/TextNoteMaster.h \
    Source/Tools.h

SOURCES += \
    Source/Clipboard.cpp \
    Source/Colors.cpp \
    Source/Main.cpp \
    Source/Record.cpp \
    Source/RecordContent.cpp \
    Source/RecordMaster.cpp \
    Source/RecordModel.cpp \
    Source/Storage.cpp \
    Source/Tag.cpp \
    Source/TagMaster.cpp \
    Source/TagModel.cpp \
    Source/TextEditHelper.cpp \
    Source/TextNote.cpp \
    Source/TextNoteMaster.cpp \
    Source/Tools.cpp \

RESOURCES += \
    Fonts/Fonts.qrc \
    Images/Images.qrc \
    Qml/Qml.qrc

QML_IMPORT_PATH = $$PWD/qml

include(Libs/sqlite/sqlite.pri)


# lupdate_only {
#     SOURCES += qml/*.qml
# }
