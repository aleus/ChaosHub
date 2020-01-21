/// @author M. A. Serebrennikov
import QtQuick 2.14
import Components 1.0
import Sp 1.0

/*******************************************************************************
 * Список записей по заданному тегу.
 ******************************************************************************/
Item {
    id: _recordList

    property alias tag: recordModel.tag

    clip: true

    Rectangle {
        id: background

        color: Colors.background
        anchors.fill: parent
    }

    RecordModel {
        id: recordModel

        tag: "root" // Debug!!! Временный флаг
    }

    ListView {
        id: listView

        delegate: TextNote {}
        model: recordModel
        verticalLayoutDirection: ListView.BottomToTop
        boundsBehavior: ListView.StopAtBounds
        spacing: Consts.spacing
        bottomMargin: Consts.spacing
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }

    // TODO Добавить таймер на удаление и восстановление
    //--------------------------------------------------------------------
    ContextMenu {
        id: contextMenu

        MenuButton {
            text: qsTr("Copy text")
            visible: contextMenu.contextObject != null
                     && contextMenu.contextObject.selectedText === ""
            onClicked: {
                Clipboard.text = contextMenu.contextObject.record.content.text;
            }
        }

        MenuButton {
            text: qsTr("Copy selected text")
            visible: contextMenu.contextObject != null
                     && contextMenu.contextObject.selectedText !== ""
            onClicked: {
                Clipboard.text = contextMenu.contextObject.selectedText;
            }
        }

        MenuButton {
            text: qsTr("Copy link")
            visible: contextMenu.contextObject != null
                     && contextMenu.contextObject.hoveredLink !== ""
            onClicked: {
                Clipboard.text = contextMenu.contextObject.hoveredLink;
            }
        }

        MenuButton {
            text: qsTr("Delete record")
            onClicked: {
                var record = contextMenu.contextObject.record;
                RecordMaster.removeRaw(record);
            }
        }
    } // ContextMenu { id: contextMenu
}
