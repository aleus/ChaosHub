/// @author M. A. Serebrennikov
import QtQuick 2.12
import Components 1.0
import Sp 1.0

/*******************************************************************************
 * Компонент для создания и редактирования записей.
 ******************************************************************************/
Item {
    id: _editor

    height: Math.max(textEdit.height, sendButton.height) + 2*Consts.spacing //+ tagsEdit.height

    Rectangle {
        color: Colors.editorBackground
        anchors.fill: parent
    }

    TextEdit {
        id: textEdit

        focus: true
        padding: Consts.spacing
        font.pixelSize: Consts.fontNormal
        color: Colors.text
        selectionColor: Colors.selection
        anchors {
            left: parent.left
            right: sendButton.left
            bottom: parent.bottom
            margins: Consts.spacing
            leftMargin: Consts.margin
            rightMargin: Consts.margin
        }

        Keys.onPressed: {
            switch (event.key) {
                case Qt.Key_Enter:
                case Qt.Key_Return:
                    if (event.modifiers & Qt.ControlModifier) {
                        console.log("text: /" + textEdit.text + "/");
                        _editor.addTextNote();
                        event.accepted = true;
                    }
                    break;
            }
        } // Keys.onPressed: {

        //KeyNavigation.onTabChanged: tagsEdit

        Text {
            id: placeholderItem

            text: qsTr("Write a note...")
            font: parent.font
            visible: parent.text === ""
            color: Colors.text
            anchors {
                top: parent.top
                left: parent.left
                margins: Consts.spacing
            }
        }
    } // TextEdit { id: textEdit

    // TextSp {
    //     id: tagsEdit

    //     focus: false
    //     DebugRectangle {}
    //     anchors {
    //         left: textEdit.left
    //         right: textEdit.right
    //         bottom: textEdit.top
    //     }
    // }

    SendButton {
        id: sendButton

        visible: textEdit.displayText !== ""
        anchors {
            right: parent.right
            bottom: parent.bottom
            rightMargin: Consts.margin
            bottomMargin: Consts.spacing
        }

        onClicked: {
            _editor.addTextNote();
        }
    } // MouseArea { id: sendButton

    //--------------------------------------------------------------------
    function addTextNote() {
        if (textEdit.text.trim() !== "") {
            TextNoteMaster.create(textEdit.text.trim());
            textEdit.text = "";
        }
    }
}
