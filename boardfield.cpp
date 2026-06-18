#include "boardfield.h"
#include <QBrush>
#include <QPen>

int BoardField::defaultWidthHeight = 80;

BoardField::BoardField(QColor backgroundColor, BoardPosition position, QGraphicsItem *parent)
    : QGraphicsRectItem(parent) {
    this->position = position;
    setRect(0, 0, defaultWidthHeight, defaultWidthHeight);
    QBrush brush(backgroundColor);
    setBrush(brush);
    setPen(Qt::NoPen);
}

BoardPosition BoardField::getPosition() {
    return position;
}
