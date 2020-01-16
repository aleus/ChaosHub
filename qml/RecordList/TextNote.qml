import QtQuick 2.14
import Components 1.0
import Sp 1.0

/*******************************************************************************
 * Делегат текстовой заметки для RecordsList. Данные берёт из одноимённого
 * класса TextNote.
 ******************************************************************************/
Item {
    id: _textNote

    width: Math.max(textItem.contentWidth, dateItem.width) + 2*textItem.anchors.leftMargin
    height: textItem.contentHeight + 2*textItem.anchors.topMargin + Consts.margin
    anchors {
        left: parent.left
        leftMargin: Consts.margin
    }

    Rectangle {
        color: Colors.noteBackground
        anchors.fill: parent
        radius: Consts.radius
    }

    //--------------------------------------------------------------------
    TextEdit {
        id: textItem

        text: record.content.textRendered
        font.pixelSize: Consts.fontNormal
        textFormat: Text.RichText
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        selectByMouse: true
        readOnly: true
        color: Colors.text
        selectionColor: Colors.selection

        width: _textNote.parent.width - 4*_textNote.anchors.leftMargin
        anchors {
            top: parent.top
            left: parent.left
            topMargin: Consts.margin
            leftMargin: Consts.margin
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: textItem.hoveredLink
                         ? Qt.PointingHandCursor
                         : Qt.ArrowCursor
            acceptedButtons: Qt.NoButton
            visible: textItem.hoveredLink
        }

        onLinkActivated: {
            Qt.openUrlExternally(RecordHelper.formatUrl(link));
        }
    } // Text { id: textItem

    //--------------------------------------------------------------------
    Text {
        id: dateItem

        text: record.dateStr
        font.pixelSize: Consts.fontSmall
        color: Colors.textSecond
        anchors {
            right: parent.right
            bottom: parent.bottom
            rightMargin: Consts.margin
            bottomMargin: Consts.spacing
        }
    }
}
