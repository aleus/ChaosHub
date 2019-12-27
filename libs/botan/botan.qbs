import qbs

StaticLibrary {
    name: "botan"
    version: "2.7"
    files: [
        "botan_all.h",
        "botan_all.cpp",
        "botan_all_internal.h",
    ]

    Depends { name: "cpp" }

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [path]
    }
}
