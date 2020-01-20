/// @author M. A. Serebrennikov
import QtQuick 2.14
import Components 1.0
import Sp 1.0

/*******************************************************************************
 * Делегат текстовой заметки для RecordsList. Данные берёт из одноимённого
 * класса TextNote.
 ******************************************************************************/
Item {
    id: _textNote

    width: textItem.lineCount <= 1
           ? Math.max(textItem.contentWidth, dateItem.width) + 2*textItem.anchors.leftMargin
           : parent.width - 2*anchors.margins
    height: textItem.contentHeight + 2*textItem.anchors.topMargin + Consts.margin
    anchors {
        left: parent.left
        margins: Consts.margin
    }

    Rectangle {
        color: Colors.noteBackground
        anchors.fill: parent
        radius: Consts.radius
    }

    //--------------------------------------------------------------------
    TextEditSp {
        id: textItem

        text: record.content.text
        font.pixelSize: Consts.fontNormal
        textFormat: Text.RichText
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        color: Colors.text
        selectionColor: Colors.selection
        selectByMouse: true
        readOnly: true
        linkColor: Colors.link
        lineHeight: 1.1

        width: _textNote.parent.width - 4*_textNote.anchors.margins
        anchors {
            top: parent.top
            left: parent.left
            topMargin: Consts.margin
            leftMargin: Consts.margin
        }

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.NoButton
            visible: textItem.hoveredLink
        }

        onLinkActivated: {
            Qt.openUrlExternally(link);
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

    //--------------------------------------------------------------------
    MouseArea {
        anchors.fill: parent
        cursorShape: textItem.hoveredLink
                     ? Qt.PointingHandCursor
                     : Qt.ArrowCursor
        acceptedButtons: Qt.RightButton
        onClicked: {
            if (textItem.hoveredLink) {
                mouse.accepted = false;
                return;
            }

            if (mouse.button == Qt.RightButton) {
                var point = mapToGlobal(mouse.x, mouse.y);
                contextMenu.open(point.x, point.y, record);
            }
        }
    }
}
