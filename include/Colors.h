/// @author M. A. Serebrennikov
#pragma once

#include <QColor>
#include <QObject>

namespace sp {

#define ColorsI Colors::instance()

/*************************************************************************//**
 * @brief Синглетон с цветами интерфейса.
 *
 * @todo Загружать цвета из файла тем.
 ****************************************************************************/
class Colors: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QColor black READ black NOTIFY changed)
    Q_PROPERTY(QColor gray0 READ gray0 NOTIFY changed)
    Q_PROPERTY(QColor gray1 READ gray1 NOTIFY changed)
    Q_PROPERTY(QColor gray2 READ gray2 NOTIFY changed)
    Q_PROPERTY(QColor red READ red NOTIFY changed)
    Q_PROPERTY(QColor green READ green NOTIFY changed)
    Q_PROPERTY(QColor blue0 READ blue0 NOTIFY changed)
    Q_PROPERTY(QColor blue1 READ blue1 NOTIFY changed)
    Q_PROPERTY(QColor white READ white NOTIFY changed)

    Q_PROPERTY(QColor text READ text NOTIFY changed)
    Q_PROPERTY(QColor textSecond READ textSecond NOTIFY changed)
    Q_PROPERTY(QColor background READ background NOTIFY changed)
    Q_PROPERTY(QColor editorBackground READ editorBackground NOTIFY changed)
    Q_PROPERTY(QColor noteBackground READ noteBackground NOTIFY changed)
    Q_PROPERTY(QColor selection READ selection NOTIFY changed)
    Q_PROPERTY(QColor link READ link NOTIFY changed)

    public:
        static Colors& instance();

        inline const QColor& black() const { return _black; }
        inline const QColor& gray0() const { return _gray0; }
        inline const QColor& gray1() const { return _gray1; }
        inline const QColor& gray2() const { return _gray2; }
        inline const QColor& green() const { return _green; }
        inline const QColor& red() const { return _red; }
        inline const QColor& white() const { return _white; }
        inline const QColor& blue0() const { return _blue0; }
        inline const QColor& blue1() const { return _blue1; }

        inline const QColor& text() const { return _text; }
        inline const QColor& textSecond() const { return _textSecond; }
        inline const QColor& background() const { return _background; }
        inline const QColor& editorBackground() const { return _editorBackground; }
        inline const QColor& noteBackground() const { return _noteBackground; }
        inline const QColor& selection() const { return _selection; }
        inline const QColor& link() const { return _link; }

    signals:
        void changed();

    private:
        Colors() = default;

    private:
        QColor _black = "#212121";
        QColor _gray0 = "#383838";
        QColor _gray1 = "#484848";
        QColor _gray2 = "#9A9A9A";
        QColor _green = "#317e04";
        QColor _red   = "#aa3030";
        QColor _blue0  = "#89A3FF";
        QColor _blue1  = "#2357A4";
        QColor _white = "white";

        QColor _text  = "white";
        QColor _textSecond = _gray2;
        QColor _background = _black;
        QColor _editorBackground = _gray0;
        QColor _noteBackground = _gray1;
        QColor _selection = _blue1;
        QColor _link = _blue0;
};

} // namespace sp
