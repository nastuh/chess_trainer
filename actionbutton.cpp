#include "actionbutton.h"
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QGraphicsTextItem>
#include "constants.h"

ActionButton::ActionButton(QString title, int width, int height) {
    setRect(0, 0, width, height);
    applyColor(Constants::buttonBg);

    textItem = new QGraphicsTextItem(title, this);
    // Увеличенный шрифт для кнопок
    QFont f("Georgia", 16, QFont::Bold);
    textItem->setFont(f);
    textItem->setDefaultTextColor(Constants::accentColor);

    leftBar = new QGraphicsRectItem(0, 0, 5, height, this);
    leftBar->setBrush(QBrush(Constants::accentColor));
    leftBar->setPen(Qt::NoPen);
    leftBar->setVisible(false);

    centerText();
    setAcceptHoverEvents(true);
}

void ActionButton::centerText() {
    double xPosition = rect().width()/2 - textItem->boundingRect().width()/2;
    double yPosition = rect().height()/2 - textItem->boundingRect().height()/2;
    textItem->setPos(xPosition, yPosition);
}

void ActionButton::applyColor(QColor color) {
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    setBrush(brush);
    QPen pen(QColor(90, 68, 38));
    pen.setWidth(2);
    setPen(pen);
}

void ActionButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    emit buttonPressed();
}

void ActionButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    applyColor(Constants::buttonHoverBg);
    textItem->setDefaultTextColor(QColor(255, 240, 210));
    leftBar->setVisible(true);
    double xPosition = rect().width()/2 - textItem->boundingRect().width()/2 + 4;
    double yPosition = rect().height()/2 - textItem->boundingRect().height()/2;
    textItem->setPos(xPosition, yPosition);
}

void ActionButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    applyColor(Constants::buttonBg);
    textItem->setDefaultTextColor(Constants::accentColor);
    leftBar->setVisible(false);
    centerText();
}
