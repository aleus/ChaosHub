import QtQuick 2.14
import QtQuick.Window 2.14
import Components 1.0
import Editor 1.0
import RecordsList 1.0

Window {
    title: qsTr("Chaos Hub")
    visible: true
    width: 640
    height: 480

    RecordsList {
        id: recordsList

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: editor.top
            bottomMargin: Consts.spacing
        }
    }

    Editor {
        id: editor

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }
}
