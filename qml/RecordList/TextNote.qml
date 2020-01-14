import QtQuick 2.14
import Components 1.0
import Sp 1.0

/*******************************************************************************
 * Делегат текстовой заметки для RecordsList. Данные берёт из одноимённого
 * класса TextNote.
 ******************************************************************************/
Item {
    id: _textNote

    anchors {
        left: parent.left
        leftMargin: Consts.margin
    }

    // width: Math.min(parent.width - 2*anchors.leftMargin
    //                 , textItem.contentWidth + 2*textItem.anchors.leftMargin)
    width: textItem.contentWidth + 2*textItem.anchors.leftMargin
    height: textItem.contentHeight + 2*textItem.anchors.topMargin

    Rectangle {
        color: "#cfcfcf"
        anchors.fill: parent
        radius: Consts.radius
    }

    Text {
        id: textItem

        text: record.content.textRendered
        font.pixelSize: Consts.fontNormal
        textFormat: Text.RichText
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        width: _textNote.parent.width - 4*_textNote.anchors.leftMargin

        anchors {
            top: parent.top
            left: parent.left
            //right: parent.right
            topMargin: Consts.margin
            leftMargin: Consts.margin
            // rightMargin: Consts.margin
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: textItem.hoveredLink
                         ? Qt.PointingHandCursor
                         : Qt.ArrowCursor
            acceptedButtons: Qt.NoButton
        }

        onTextChanged: {
            const rx = /\b((?:https?:\/\/|www\d{0,3}[.]|[a-z0-9.\-]+[.][a-z]{1,4}|localhost\/?)(?:[^\s()<>]+|\((?:[^\s()<>]+|(?:\([^\s()<>]+\)))*\))+)/gmi;
            if (rx.test(record.content.text)) {
                console.log("Yes it is link: " + record.content.textRendered);
            }
        }

        onLinkActivated: {
            console.log("link: " + link);
            Qt.openUrlExternally(RecordHelper.formatUrl(link));
        }
    } // Text { id: textItem
}
