/// @author M. A. Serebrennikov
import QtQuick 2.14
import Components 1.0
import Sp 1.0

/*******************************************************************************
 * Компонент для создания и редактирования записей.
 ******************************************************************************/
Item {
    id: _editor

    height: Math.max(textEdit.height, sendButton.height) + 2*Consts.spacing

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
            margins: Consts.spacing
            leftMargin: Consts.margin
            rightMargin: Consts.margin
            verticalCenter: parent.verticalCenter
        }

        Text {
            id: placeholder

            text: qsTr("Write a note...")
            font: parent.font
            visible: parent.text == ""
            color: Colors.text
            anchors {
                top: parent.top
                left: parent.left
                margins: Consts.spacing
            }
        }

        Keys.onPressed: {
            switch (event.key) {
                case Qt.Key_Enter:
                case Qt.Key_Return:
                    if (event.modifiers & Qt.ControlModifier) {
                        _editor.addTextNote();
                        event.accepted = true;
                    }
                    break;
            }
        } // Keys.onPressed: {
    } // TextEdit { id: textEdit

    SendButton {
        id: sendButton
        anchors {
            right: parent.right
            bottom: parent.bottom
            margins: Consts.spacing
        }
    } // MouseArea { id: sendButton

    //--------------------------------------------------------------------
    function addTextNote() {
        console.log("addTextNote");
        TextNoteMaster.create(textEdit.text);
        textEdit.text = "";
    }
}
