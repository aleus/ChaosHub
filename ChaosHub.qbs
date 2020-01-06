import qbs

Project {
    references: [
        "libs/sqlite/sqlite.qbs",
        "libs/botan/botan.qbs",
    ]

    Application {

        files: [
            "README.md",
            "include/ChaosTypedef.h",
            "include/Record.h",
            "include/RecordContent.h",
            "include/RecordsMaster.h",
            "include/RecordsModel.h",
            "include/Storage.h",
            "include/TextNote.h",
            "source/Record.cpp",
            "source/RecordsMaster.cpp",
            "source/RecordsModel.cpp",
            "source/Storage.cpp",
            "source/TextNote.cpp",
            "source/main.cpp",
            "qml/qml.qrc",
            "translations/ChaosHub_ru_RU.ts",
        ]

        cpp.cxxLanguageVersion: "c++17"
        cpp.includePaths: ["include"]
        cpp.defines: [
            "QT_DEPRECATED_WARNINGS",
        ]

        property pathList qmlImportPaths: ["qml"]

        Depends { name: "Qt"; submodules: ["core", "quick"] }
        Depends { name: "sqlite" }
        Depends { name: "botan" }

        Group {
            fileTagsFilter: "application"
            qbs.install: true
            qbs.installDir: "bin"
        }
    }
}
