#ifndef ACTIONBUTTON_H
#define ACTIONBUTTON_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsTextItem>

class ActionButton: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    ActionButton(QString title, int width = 220, int height = 50);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void buttonPressed();

private:
    void applyColor(QColor color);
    void centerText();
    QGraphicsTextItem *textItem;
    QGraphicsRectItem *leftBar;
};

#endif // ACTIONBUTTON_H
