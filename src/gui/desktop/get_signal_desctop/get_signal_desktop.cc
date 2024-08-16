#include "get_signal_desktop.h"

Signal GetSignalDesktop(QKeyEvent *event)
{
    Signal signal = kNosig;
    switch (event->key())
    {
    case Qt::Key_Escape:
        signal = kExit;
        break;
    case Qt::Key_Up:
        signal = kMoveUp;
        break;
    case Qt::Key_Down:
        signal = kMoveDown;
        break;
    case Qt::Key_Left:
        signal = kMoveLeft;
        break;
    case Qt::Key_Right:
        signal = kMoveRight;
        break;
    case Qt::Key_Q:
        signal = kRotateLeft;
        break;
    case Qt::Key_E:
        signal = kRotateRight;
        break;
    case Qt::Key_Space:
        signal = kPause;
        break;
    case Qt::Key_Enter:
        signal = kStartSig;
        break;
    default:
        signal = kNosig;
        break;
    }

    return signal;
}
