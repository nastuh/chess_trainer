#ifndef BOARDVIEW_H
#define BOARDVIEW_H
#include <QGraphicsRectItem>
#include <QList>
#include <QPoint>
#include "boardfield.h"
#include "pawnfield.h"

class BoardView: public QGraphicsRectItem {
public:
    BoardView();
    static int numberOfRowsColumns;
    static int startXPosition;
    static int startYPosition;

    QList<BoardField*> getFields();
    void draw();
    void initializePawnFields(QList<BasePawnModel*> pawns);
    PawnField* getPawnAtBoardPosition(BoardPosition boardPosition);
    PawnField* getPawnAtMousePosition(QPoint point);
    void moveActivePawnToMousePosition(QPoint point, BasePawnModel *pawn);
    void placeActivePawnAtBoardPosition(BasePawnModel *pawn, BoardPosition boardPosition);
    void removePawnAtBoardPosition(BoardPosition boardPosition);
    void setPawnMoveCheckWarning(bool visible);
    void promotePawnAtBoardPosition(BoardPosition boardPosition);
    void highlightMoves(QList<BoardPosition> positions);
    void clearHighlights();
    void highlightSelectedPawn(BoardPosition bp);

private:
    QList<BoardField*> fields;
    QList<PawnField*> pawns;
    QList<QGraphicsItem*> highlightItems;
    QGraphicsTextItem *checkWarningTitleTextItem;
    QGraphicsTextItem *checkWarningDescriptionTextItem;

    void placeBoardFields();
    void createFieldsColumn(int xPosition, int columnNumber);
    void drawBoardFrame();
    void drawCheckWarningTextItems();
    QPointF getCoordinatesForBoardPosition(BoardPosition position);
};
#endif
