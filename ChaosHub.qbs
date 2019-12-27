import qbs

Project {
    references: [
        "libs/sqlite/sqlite.qbs",
        "libs/botan/botan.qbs",
    ]

    Application {

        files: [
            "README.md",
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
