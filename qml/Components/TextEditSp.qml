/// @author M. A. Serebrennikov
import QtQuick 2.14
import Sp 1.0

/*******************************************************************************
 * Текстовый многострочный редактор. Имеет расширенное количество параметров.
 * К примеру, позволяет установить межстрочный интервал.
 *
 * Для работы вместо параметра text нужно использовать textBase
 ******************************************************************************/
TextEdit {
    id: _textEditSp

    property alias text: _helper.text
    property alias linkColor: _helper.linkColor
    property alias lineHeight: _helper.lineHeight

    textFormat: Text.RichText

    TextEditHelper {
        id: _helper

        textDocument: _textEditSp.textDocument
    }

    Component.onCompleted: {
        _helper.format();
    }
}
