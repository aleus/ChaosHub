import QtQuick 2.14
import Components 1.0
import Sp 1.0 as Sp

/*******************************************************************************
 * Список записей по заданному тегу.
 ******************************************************************************/
Item {
    id: _recordsList

    property alias tag: recordsModel.tag

    Sp.RecordsModel {
        id: recordsModel

        tag: "root" // Debug!!! Временный флаг
    }

    ListView {
        id: listView

        delegate: TextNote {}
        model: recordsModel
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }
}
