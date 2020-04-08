/// @author M. A. Serebrennikov
import QtQuick 2.12
import Components 1.0
import Sp 1.0

/*******************************************************************************
 * Кнопка для отправки новой заметки в хранилище.
 ******************************************************************************/
MouseArea {
    id: sendButton
    
    width: height
    height: Consts.buttonHeight

    Image {
        id: imageItem

        source: "qrc:/RightArrow.svg"
        fillMode: Image.PreserveAspectFit
        height: Consts.imageInButtonHeight
        sourceSize: Qt.size(width, height)
        anchors.centerIn: parent
    }
}
