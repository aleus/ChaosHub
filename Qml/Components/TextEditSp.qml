/// @author M. A. Serebrennikov
import QtQuick 2.12
import Sp 1.0

/*******************************************************************************
 * Текстовый многострочный редактор. Имеет расширенное количество параметров.
 * К примеру, позволяет установить межстрочный интервал.
 *
 * Для работы вместо параметра text нужно использовать textBase
 ******************************************************************************/
Item {
    id: _textEditSp

    property alias color: textEdit.color
    property alias font: textEdit.font
    property alias hoveredLink: textEdit.hoveredLink
    property alias lineHeight: _helper.lineHeight
    property alias linkColor: _helper.linkColor
    property alias padding: textEdit.padding
    property alias placeholderText: placeholder.text
    property alias selectByMouse: textEdit.selectByMouse
    property alias selectedText: textEdit.selectedText
    property alias selectionColor: textEdit.selectionColor
    property alias text: _helper.rawText
    property alias textFormat: textEdit.textFormat
    property alias wrapMode: textEdit.wrapMode
    property alias readOnly: textEdit.readOnly
    property alias contentWidth: textEdit.contentWidth
    property alias contentHeight: textEdit.contentHeight

    signal linkActivated(var link)

    height: textEdit.height

    TextEdit {
        id: textEdit

        text: _helper.rawText
        focus: true
        textFormat: Text.RichText
        width: parent.width
        onLinkActivated: {
            _textEditSp.linkActivated(link)
        }
    }

    TextEditHelper {
        id: _helper

        linkColor: Colors.link
        lineHeight: 1.1
        textDocument: textEdit.textDocument
    }

    Text {
        id: placeholder

        font: parent.font
        visible: parent.text === ""
        color: Colors.text
        anchors {
            top: parent.top
            left: parent.left
            margins: Consts.spacing
        }
    }
}
