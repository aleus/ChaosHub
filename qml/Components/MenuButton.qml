/// @author M. A. Serebrennikov
import QtQuick 2.12
import Sp 1.0

/*******************************************************************************
 * Кнопка с текстом в контекстном меню. Автоматически подстраивает ширину
 * под максимальную ширину списка кнопок.
 ******************************************************************************/
Item {
    id: _menuButton

    property alias text: textItem.text
    readonly property var contextMenu: parent.contextMenu

    signal clicked(var mouse)
    
    implicitWidth: textItem.contentWidth + 2*textItem.anchors.margins
    width: parent.maxWidth
    height: Consts.buttonHeight

    Rectangle {
        id: highlight

        color: Colors.highlight
        visible: mouseArea.containsMouse
        anchors.fill: parent
    }
    
    Text {
        id: textItem

        color: Colors.text
        font.pixelSize: Consts.fontNormal
        anchors {
            left: parent.left
            margins: Consts.margin
            verticalCenter: parent.verticalCenter
        }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        hoverEnabled: true
        enabled: _menuButton.enabled
        onClicked: {
            _menuButton.clicked(mouse);
            if (mouse.accepted) {
                contextMenu.close();
            }
        }
    }

    onImplicitWidthChanged: {
        parent.maxWidth = Math.max(implicitWidth, parent.maxWidth);
    }
}
