#ifndef PAWNVIEWMODEL_H
#define PAWNVIEWMODEL_H

#include <QString>
#include "basepawnmodel.h"
#include "boardposition.h"

class PawnViewModel {
public:
    PawnViewModel() {}
    PawnType getTypeForInitialPosition(BoardPosition position) {
        if (position.y == 1 || position.y == 6) return PawnType::pawn;
        switch(position.x) {
            case 0: case 7: return PawnType::rook;
            case 1: case 6: return PawnType::knight;
            case 2: case 5: return PawnType::bishop;
            case 3: return PawnType::queen;
            case 4: return PawnType::king;
        }
        return PawnType::pawn;
    }
    QString getImagePath(PawnType type, PlayerType owner) {
        QString color = (owner == PlayerType::white) ? "white" : "black";
        switch(type) {
            case PawnType::king:   return QString(":/Images/king_%1.svg").arg(color);
            case PawnType::queen:  return QString(":/Images/queen_%1.svg").arg(color);
            case PawnType::rook:   return QString(":/Images/rook_%1.svg").arg(color);
            case PawnType::bishop: return QString(":/Images/bishop_%1.svg").arg(color);
            case PawnType::knight: return QString(":/Images/knight_%1.svg").arg(color);
            case PawnType::pawn:   return QString(":/Images/pawn_%1.svg").arg(color);
        }
        return "";
    }
    QString getPromotedImagePath(PlayerType owner) {
        return getImagePath(PawnType::queen, owner);
    }
};

#endif
