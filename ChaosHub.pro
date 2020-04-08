QT += quick quickcontrols2 widgets network multimedia svg xml

CONFIG += c++17

INCLUDEPATH += \
    include \

HEADERS += \ \
    include/Clipboard.h \
    include/Colors.h \
    include/Defer.h \
    include/PointersTypedef.h \
    include/Record.h \
    include/RecordContent.h \
    include/RecordMaster.h \
    include/RecordModel.h \
    include/Storage.h \
    include/Tag.h \
    include/TagMaster.h \
    include/TagModel.h \
    include/TextEditHelper.h \
    include/TextNote.h \
    include/TextNoteMaster.h \
    include/Tools.h

SOURCES += \
    source/Clipboard.cpp \
    source/Colors.cpp \
    source/Main.cpp \
    source/Record.cpp \
    source/RecordContent.cpp \
    source/RecordMaster.cpp \
    source/RecordModel.cpp \
    source/Storage.cpp \
    source/Tag.cpp \
    source/TagMaster.cpp \
    source/TagModel.cpp \
    source/TextEditHelper.cpp \
    source/TextNote.cpp \
    source/TextNoteMaster.cpp \
    source/Tools.cpp \

# lupdate_only {
#     SOURCES += qml/*.qml
# }

RESOURCES += \
    fonts/fonts.qrc \
    qml/qml.qrc

QML_IMPORT_PATH = $$PWD/qml

include(libs/sqlite/sqlite.pri)
