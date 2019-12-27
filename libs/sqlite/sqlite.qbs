import qbs

StaticLibrary {
    name: "sqlite"
    version: "3.25"
    files: [
        "sqlite3.c",
        "sqlite3.h",
    ]

    Depends { name: "cpp" }
    cpp.defines: [
        "SQLITE_ENABLE_FTS5"
    ]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [path]
    }
}
