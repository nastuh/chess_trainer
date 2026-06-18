#include "playerview.h"
#include <QObject>
#include <QFont>
#include "constants.h"
#include "gameview.h"
#include "utils.h"

int PlayerView::defaultWidthHeight = 0; // Not used in new layout
extern GameView *game;

PlayerView::PlayerView(QGraphicsItem *parent): QGraphicsRectItem(parent) {
    setPen(Qt::NoPen);
    setBrush(Qt::NoBrush);
    checkTextItem = nullptr;
}

void PlayerView::setPlayer(PlayerType owner) {
    // No-op in new layout; timer display is in the right panel
    Q_UNUSED(owner);
}

void PlayerView::setActive(bool active) {
    Q_UNUSED(active);
}

void PlayerView::setIsInCheck(bool isCheck) {
    Q_UNUSED(isCheck);
}
