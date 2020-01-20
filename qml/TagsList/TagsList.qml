/// @author M. A. Serebrennikov
import QtQuick 2.14
import Components 1.0
import Sp 1.0

/*******************************************************************************
 * Иеархический список тегов(категорий).
 ******************************************************************************/
Item {
    id: _tagsList

    clip: true
    width: Consts.buttonHeight

    Text {
        id: placeholder

        text: qsTr("Tags list will been here soon")
        font.pixelSize: Consts.fontNormal
        color: Colors.text
        anchors.centerIn: parent
        rotation: -90
    }
}
