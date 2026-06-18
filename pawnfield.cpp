#include "pawnfield.h"
#include <QGraphicsProxyWidget>
#include "boardfield.h"
#include "boardposition.h"
#include "gameview.h"
#include "utils.h"

extern GameView *game;

PawnField::PawnField(BoardPosition position,
                     QString imagePath,
                     QGraphicsItem *parent): QGraphicsRectItem(parent) {
    this->position = position;
    imageLabel = new QLabel();
    QPixmap original(imagePath);
    image = original.scaled(BoardField::defaultWidthHeight, BoardField::defaultWidthHeight,
                            Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsProxyWidget *pMyProxy = new QGraphicsProxyWidget(this);

    imageLabel->setPixmap(image);
    imageLabel->setAttribute(Qt::WA_TranslucentBackground);
    imageLabel->setAlignment(Qt::AlignCenter);
    pMyProxy->setWidget(imageLabel);

    setPen(Qt::NoPen);
}

void PawnField::setPosition(BoardPosition position) {
    this->position = position;
}

void PawnField::setImage(QString imagePath) {
    QPixmap original(imagePath);
    image = original.scaled(BoardField::defaultWidthHeight, BoardField::defaultWidthHeight,
                            Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imageLabel->clear();
    imageLabel->setPixmap(image);
}

BoardPosition PawnField::getPosition() {
    return position;
}
