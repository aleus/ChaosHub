import QtQuick 2.14
import Components 1.0
import Sp 1.0

/*******************************************************************************
 * Кнопка для отправки новой заметки в хранилище.
 ******************************************************************************/
MouseArea {
    id: sendButton
    
    width: Consts.buttonHeight
    height: width
    
    Rectangle {
        color: Colors.gray1
        anchors.fill: parent
    }
    
    onClicked: {
        _editor.addTextNote();
    }
}
