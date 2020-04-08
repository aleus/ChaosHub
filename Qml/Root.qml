/// @author M. A. Serebrennikov
import QtQuick 2.12
import QtQuick.Window 2.12
import Components 1.0
import TagsList 1.0
import Editor 1.0
import RecordList 1.0
import Sp 1.0

Window {
    title: qsTr("Chaos Hub")
    visible: true
    width: 640
    height: 480
    color: Colors.background

    TagsList {
        id: tagsList

        anchors {
            top: parent.top
            left: parent.left
            bottom: parent.bottom
        }
    }

    RecordList {
        id: recordsList

        anchors {
            top: parent.top
            left: tagsList.right
            right: parent.right
            bottom: editor.top
        }
    }

    Editor {
        id: editor

        anchors {
            left: recordsList.left
            right: parent.right
            bottom: parent.bottom
        }
    }
}
