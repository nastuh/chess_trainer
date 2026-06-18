#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include "basepawnmodel.h"

class PlayerView: public QGraphicsRectItem {
public:
    static int defaultWidthHeight;
    PlayerView(QGraphicsItem *parent = nullptr);
    void setPlayer(PlayerType owner);
    void setActive(bool active);
    void setIsInCheck(bool isCheck);
private:
    QGraphicsTextItem *checkTextItem;
};
#endif
