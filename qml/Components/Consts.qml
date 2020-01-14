pragma Singleton

import QtQuick 2.14

QtObject {
    readonly property real spacing: 5*dp
    readonly property real margin: 10*dp
    readonly property real marginMiddle: 20*dp
    readonly property real fontBig: 40*dp
    readonly property real fontNormal: 12*dp
    readonly property real fontSmall: 9*dp

    readonly property real buttonHeight: 24*dp
    readonly property real radius: 3*dp

    readonly property color colorBlack: "black"
    readonly property color colorGray0: "#888888"
    readonly property color colorGray1: "#cfcfcf"
    readonly property color colorGray2: "#828282"
    readonly property color colorGreen: "#317e04"
    readonly property color colorRed: "#aa3030"
    readonly property color colorWhite: "white"

    // Records
    readonly property color colorNoteBackground: colorGray1
    readonly property color colorTextSecond: colorGray2
    readonly property color colorText: colorBlack
}
