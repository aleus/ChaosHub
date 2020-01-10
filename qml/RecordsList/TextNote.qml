import QtQuick 2.14
import Components 1.0

/*******************************************************************************
 * Делегат текстовой заметки для RecordsList. Данные берёт из одноимённого
 * класса TextNote.
 ******************************************************************************/
Item {
    id: _textNote

    width: parent.width
    height: textItem.contentHeight + 2*Consts.marginMiddle

    Text {
        id: textItem

        text: record.content.text
        font.pixelSize: Consts.fontNormal
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            topMargin: Consts.marginMiddle
            leftMargin: Consts.margin
            rightMargin: Consts.margin
        }
    }

    Component.onCompleted: {
        console.log("item completed");
    }
}
