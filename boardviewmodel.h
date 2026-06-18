#ifndef BOARDVIEWMODEL_H
#define BOARDVIEWMODEL_H

#include <QList>
#include <QPoint>
#include "basepawnmodel.h"
#include "pawnfield.h"
#include "pawnviewmodel.h"

class BoardViewModel {
public:
    BoardViewModel();

    QList<BasePawnModel*> getBlackPawns();
    QList<BasePawnModel*> getWhitePawns();
    BasePawnModel* getActivePawn();
    PlayerType getWhosTurn();
    PlayerType* getWinner();

    void setActivePawnForField(PawnField *pawn);
    void setNewPositionForActivePawn(BoardPosition position);
    void discardActivePawn();

    BasePawnModel* getPawnOnBoardPosition(BoardPosition boardPosition);
    bool validatePawnPalcementForMousePosition(QPoint point);
    bool validatePawnMove(BoardPosition positionToMove, BasePawnModel *pawn = nullptr, BoardPosition *requestedActivePawnPosition = nullptr);
    bool didRemoveEnemyOnBoardPosition(BoardPosition boardPosition);
    bool isKingInCheck(PlayerType owner, bool isCheckingActivePlayer = false, BoardPosition positionToMoveActivePlayer = {0,0});
    bool didPromoteActivePawn();
    void switchRound();
    BoardPosition getBoardPositionForMousePosition(QPoint point);

    void reset();

private:
    QList<BasePawnModel*> blackPawns;
    QList<BasePawnModel*> whitePawns;
    BasePawnModel *activePawn;
    PlayerType whosTurn;
    bool isEnPassantAvailable;
    PawnViewModel pawnViewModel;
    PlayerType *winner;

    void initializePawns();
    void initializePawnsForRow(int rowNumber, PlayerType owner);
    bool validateAnotherPawnIntersection(BoardPosition positionToMove, BasePawnModel *pawnToValidate, BoardPosition *requestedActivePawnPosition = nullptr);
    bool validateKingsCheckForPawns(QList<BasePawnModel*> pawns, bool isCheckingActivePlayer, BasePawnModel *king, BoardPosition positionToMoveActivePlayer);
};

#endif
