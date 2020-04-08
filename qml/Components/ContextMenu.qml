/// @author M. A. Serebrennikov
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import Sp 1.0

/*******************************************************************************
 * @brief Базовый компонент для контекстного меню.
 *
 * @details Контекстное меню отображает вертикальный список MenuButton.
 * Для показа контекстного меню нужно вызвать метод open(x,y,object), где
 * x,y - абсолютные координаты на экране, а object - контекстный объект,
 * доступный для обрабтки в MenuButton.
 *
 * @todo Разобратья как обойти глюк Qt с прозрачным полноэкранным окном в Windows.
 ******************************************************************************/
Window {
    id: _contextMenu

    default property alias content: column.children
    readonly property alias contextObject: _private.contextObject

    color: "transparent"
    flags: Qt.platform.os === "windows" ? Qt.SplashScreen : Qt.Window // Костыль, т.к. полноэкранный режим в Windows глючит с прозрачным цветом окна

    MouseArea {
        id: hideMA

        anchors.fill: parent
        acceptedButtons: Qt.AllButtons
        onClicked: {
            close();
        }
    }

    //--------------------------------------------------------------------
    Rectangle {
        id: container

        color: Colors.popupBackground
        width: column.width
        height: column.height
        visible: false

        MouseArea {
            id: dummyMa

            anchors.fill: parent
            acceptedButtons: Qt.AllButtons
            onClicked: {  }
        }

        Column {
            id: column

            property int maxWidth: 0
            property alias contextMenu: _contextMenu
        } // Column { id: column
    } //Rectangle { id: container

    //--------------------------------------------------------------------
    QtObject {
        id: _private

        property var contextObject
    }

    onVisibleChanged: {
        if (!visible) {
            _private.contextObject = null;
        }
    }

    /**
     * @brief Показываем контекстное меню в заданной точке экрана.
     * @param object текущий объект для обработки в контекстном меню.
     */
    function open(x, y, object) {
        _private.contextObject = object;

        // Костыль, т.к. полноэкранный режим в Windows глючит с прозрачным цветом окна
        if (Qt.platform.os === "windows") {
            showMaximized();
        } else {
            showFullScreen();
        }

        container.x = Math.min(x, _contextMenu.width - container.width);
        container.y = Math.min(y+1, _contextMenu.height - container.height);
        container.visible = true;
    }
}
