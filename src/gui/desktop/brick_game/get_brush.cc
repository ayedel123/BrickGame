#include "get_brush.h"


QBrush GetBrush(int color){
    QBrush brush;
    switch(color) {
    case 1:
        brush = QBrush(Qt::red, Qt::SolidPattern);
        break;
    case 2:
        brush = QBrush(Qt::green, Qt::SolidPattern);
        break;
    case 3:
        brush = QBrush(QColorConstants::Svg::orange, Qt::SolidPattern);
        break;
    case 4:
        brush = QBrush(QColor(102, 102, 255), Qt::SolidPattern);
        break;
    case 5:
        brush = QBrush(QColor(178, 102, 255), Qt::SolidPattern);
        break;
    case 6:
        brush = QBrush(Qt::yellow, Qt::SolidPattern);
        break;
    case 7:
        brush = QBrush(QColor(255, 0, 127), Qt::SolidPattern);
        break;
    default:
        brush = QBrush(Qt::black, Qt::SolidPattern);
        break;
    }

    return brush;


}
