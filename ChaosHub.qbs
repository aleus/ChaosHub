import qbs

Project {
    references: [
        "libs/sqlite/sqlite.qbs",
        // Botan временно отключен до реализации шифрования
        // "libs/botan/botan.qbs",
    ]

    Application {
        files: [
            "README.md",
            "fonts/fonts.qrc",
            "include/Clipboard.h",
            "include/Colors.h",
            "include/Defer.h",
            "include/PointersTypedef.h",
            "include/Record.h",
            "include/RecordContent.h",
            "include/RecordMaster.h",
            "include/RecordModel.h",
            "include/Storage.h",
            "include/Tag.h",
            "include/TagMaster.h",
            "include/TagModel.h",
            "include/TextEditHelper.h",
            "include/TextNote.h",
            "include/TextNoteMaster.h",
            "include/Tools.h",
            "source/Clipboard.cpp",
            "source/Colors.cpp",
            "source/Record.cpp",
            "source/RecordContent.cpp",
            "source/RecordMaster.cpp",
            "source/RecordModel.cpp",
            "source/Storage.cpp",
            "source/Tag.cpp",
            "source/TagMaster.cpp",
            "source/TagModel.cpp",
            "source/TextEditHelper.cpp",
            "source/TextNote.cpp",
            "source/TextNoteMaster.cpp",
            "source/Tools.cpp",
            "source/main.cpp",
            "qml/qml.qrc",
            "translations/ChaosHub_ru_RU.ts",
        ]

        cpp.cxxLanguageVersion: "c++17"
        cpp.includePaths: ["include"]

        property pathList qmlImportPaths: [
            sourceDirectory + "/qml",
        ]

        Depends { name: "Qt"; submodules: ["core", "quick", "widgets"] }
        Depends { name: "sqlite" }
        // Depends { name: "botan" }

        Group {
            fileTagsFilter: "application"
            qbs.install: true
            qbs.installDir: "bin"
        }
    }
}
