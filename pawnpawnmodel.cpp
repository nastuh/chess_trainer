#include "pawnpawnmodel.h"

PawnPawnModel::PawnPawnModel(BoardPosition position, PlayerType owner, PawnType type, QString imagePath)
    : BasePawnModel(position, owner, type, imagePath) {}

bool PawnPawnModel::validateMove(BoardPosition positionToMove, BasePawnModel *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition) {
    int yDir = (owner == PlayerType::white) ? -1 : 1;
    int dx = positionToMove.x - position.x;
    int dy = positionToMove.y - position.y;

    // Forward move
    if (dx == 0 && dy == yDir && !pawnOnPositionToMove) return true;
    // First double move
    if (dx == 0 && dy == 2*yDir && !didTakeFirstMove && !pawnOnPositionToMove) return true;
    // Diagonal capture
    if (abs(dx) == 1 && dy == yDir && pawnOnPositionToMove && pawnOnPositionToMove->owner != owner) return true;

    return false;
}
