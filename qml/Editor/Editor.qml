import QtQuick 2.14
import Components 1.0
import Sp 1.0

/*******************************************************************************
 * Компонент для создания и редактирования записей.
 ******************************************************************************/
Item {
    id: _editor

    height: Math.max(textEdit.height, sendButton.height) + 2*Consts.spacing

    TextEdit {
        id: textEdit

        focus: true
        padding: Consts.spacing
        font.pixelSize: Consts.fontNormal
        anchors {
            left: parent.left
            right: sendButton.left
            margins: Consts.spacing
            leftMargin: Consts.margin
            rightMargin: Consts.margin
            verticalCenter: parent.verticalCenter
        }

        DebugRectangle {}

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

    MouseArea {
        id: sendButton

        width: Consts.buttonHeight
        height: width
        anchors {
            right: parent.right
            bottom: parent.bottom
            margins: Consts.spacing
        }

        Rectangle {
            color: Consts.colorGray
            anchors.fill: parent
        }

        onClicked: {
            _editor.addTextNote();
        }
    } // MouseArea { id: sendButton

    //--------------------------------------------------------------------
    function addTextNote() {
        console.log("addTextNote");
        TextNoteMaster.create(textEdit.text);
    }
}
