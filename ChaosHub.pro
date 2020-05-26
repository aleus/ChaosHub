QT += quick quickcontrols2 widgets network multimedia svg xml

CONFIG += c++17

INCLUDEPATH += \
    Source \
    Source/Masters \
    Source/Models \
    Source/Records \
    Source/TextSp \
    Source/Tools \

HEADERS += \
    Source/Masters/RecordMaster.h \
    Source/Masters/TagMaster.h \
    Source/Masters/TextNoteMaster.h \
    Source/Models/RecordModel.h \
    Source/Models/TagModel.h \
    Source/PointersTypedef.h \
    Source/Records/AbstractRecord.h \
    Source/Records/Category.h \
    Source/Records/Record.h \
    Source/Records/RecordContent.h \
    Source/Records/Tag.h \
    Source/Records/TextNote.h \
    Source/Storage.h \
    Source/TextSp/TextHelper.h \
    Source/Tools/Clipboard.h \
    Source/Tools/Colors.h \
    Source/Tools/Defer.h \
    Source/Tools/Tools.h

SOURCES += \
    Source/Category.cpp \
    Source/Main.cpp \
    Source/Masters/RecordMaster.cpp \
    Source/Masters/TagMaster.cpp \
    Source/Masters/TextNoteMaster.cpp \
    Source/Models/RecordModel.cpp \
    Source/Models/TagModel.cpp \
    Source/Records/AbstractRecord.cpp \
    Source/Records/Record.cpp \
    Source/Records/RecordContent.cpp \
    Source/Records/Tag.cpp \
    Source/Records/TextNote.cpp \
    Source/Storage.cpp \
    Source/TextSp/TextHelper.cpp \
    Source/Tools/Clipboard.cpp \
    Source/Tools/Colors.cpp \
    Source/Tools/Tools.cpp \

RESOURCES += \
    Fonts/Fonts.qrc \
    Images/Images.qrc \
    Qml/Qml.qrc

QML_IMPORT_PATH = $$PWD/qml

include(Libs/sqlite/sqlite.pri)


# lupdate_only {
#     SOURCES += qml/*.qml
# }
