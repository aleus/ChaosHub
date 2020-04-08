/// @author M. A. Serebrennikov
import QtQuick 2.12
import Components 1.0
import Sp 1.0

/*******************************************************************************
 * Кнопка для отправки новой заметки в хранилище.
 ******************************************************************************/
MouseArea {
    id: sendButton
    
    height: Consts.buttonHeight
    width: height
    
    Rectangle {
        color: Colors.gray1
        anchors.fill: parent
    }
    
    onClicked: {
        _editor.addTextNote();
    }
}
