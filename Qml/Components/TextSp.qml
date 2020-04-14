/// @author M. A. Serebrennikov
import QtQuick 2.12
import Sp 1.0

/*******************************************************************************
 * Текстовый многострочный редактор. Имеет расширенное количество параметров.
 * К примеру, позволяет установить межстрочный интервал.
 *
 * Для работы вместо параметра text нужно использовать textBase
 ******************************************************************************/
TextEdit {
    id: _textEditSp

    property alias lineHeight: helper.lineHeight
    property alias linkColor: helper.linkColor

    signal linkActivated(var link)

    textFormat: Text.PlainText
    onLinkActivated: {
        _textEditSp.linkActivated(link)
    }

    TextHelper {
        id: helper

        linkColor: Colors.link
        lineHeight: 1.1
        textDocument: _textEditSp.textDocument
    }
}
