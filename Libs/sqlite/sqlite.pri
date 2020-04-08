INCLUDEPATH += \
    $$PWD \

HEADERS += \
    $$PWD/sqlite3.h

SOURCES += \
    $$PWD/sqlite3.c

DEFINES += SQLITE_ENABLE_FTS5
