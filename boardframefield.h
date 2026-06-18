#ifndef BOARDFRAMEFIELD_H
#define BOARDFRAMEFIELD_H
#include <QGraphicsRectItem>
class BoardFrameField : public QGraphicsRectItem {
public:
    BoardFrameField(QGraphicsItem *parent = nullptr) : QGraphicsRectItem(parent) {}
};
#endif
