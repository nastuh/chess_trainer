#include "boardview.h"
#include "boardfield.h"
#include "pawnfield.h"
#include "constants.h"
#include "utils.h"
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QGraphicsEllipseItem>

int BoardView::numberOfRowsColumns = 8;
int BoardView::startXPosition = 0;
int BoardView::startYPosition = 0;

BoardView::BoardView() : QGraphicsRectItem() {
    int size = BoardField::defaultWidthHeight * numberOfRowsColumns;
    setRect(0, 0, size + 50, size + 50);
    setPen(Qt::NoPen);
    QBrush bg(QColor(50,35,20));
    setBrush(bg);
    checkWarningTitleTextItem = nullptr;
    checkWarningDescriptionTextItem = nullptr;
}

void BoardView::draw() {
    startXPosition = static_cast<int>(x()) + 25;
    startYPosition = static_cast<int>(y()) + 25;
    placeBoardFields();
    drawBoardFrame();
    drawCheckWarningTextItems();
}

void BoardView::placeBoardFields() {
    for (int col = 0; col < numberOfRowsColumns; col++) {
        createFieldsColumn(col * BoardField::defaultWidthHeight, col);
    }
}

void BoardView::createFieldsColumn(int xPos, int colNumber) {
    for (int row = 0; row < numberOfRowsColumns; row++) {
        bool isLight = (colNumber + row) % 2 == 0;
        QColor color = isLight ? Constants::lightSquare : Constants::darkSquare;
        BoardPosition pos = { colNumber, row };
        BoardField *field = new BoardField(color, pos, this);
        field->setPos(25 + xPos, 25 + row * BoardField::defaultWidthHeight);
        fields.append(field);
    }
}

void BoardView::drawBoardFrame() {
    // Column labels A-H
    QStringList cols = {"A","B","C","D","E","F","G","H"};
    QStringList rows = {"8","7","6","5","4","3","2","1"};
    QFont labelFont("Georgia", 11, QFont::Bold);
    for (int i = 0; i < 8; i++) {
        // Bottom column labels
        QGraphicsTextItem *colLabel = new QGraphicsTextItem(cols[i], this);
        colLabel->setFont(labelFont);
        colLabel->setDefaultTextColor(Constants::accentColor);
        colLabel->setPos(25 + i * BoardField::defaultWidthHeight + 30, 25 + 8 * BoardField::defaultWidthHeight + 4);
        // Left row labels
        QGraphicsTextItem *rowLabel = new QGraphicsTextItem(rows[i], this);
        rowLabel->setFont(labelFont);
        rowLabel->setDefaultTextColor(Constants::accentColor);
        rowLabel->setPos(4, 25 + i * BoardField::defaultWidthHeight + 28);
    }
}

void BoardView::drawCheckWarningTextItems() {
    checkWarningTitleTextItem = new QGraphicsTextItem("", this);
    checkWarningDescriptionTextItem = new QGraphicsTextItem("", this);
    checkWarningTitleTextItem->setDefaultTextColor(QColor(220,50,50));
    checkWarningDescriptionTextItem->setDefaultTextColor(QColor(220,50,50));
    QFont f("Georgia",12,QFont::Bold);
    checkWarningTitleTextItem->setFont(f);
    checkWarningTitleTextItem->setPos(25, 5);
    checkWarningDescriptionTextItem->setFont(QFont("Georgia",10));
    checkWarningDescriptionTextItem->setPos(25, 20);
    checkWarningTitleTextItem->setVisible(false);
    checkWarningDescriptionTextItem->setVisible(false);
}

QList<BoardField*> BoardView::getFields() { return fields; }

void BoardView::initializePawnFields(QList<BasePawnModel*> pawns) {
    for (auto *model : pawns) {
        PawnField *pf = new PawnField(model->position, model->imagePath, this);
        QPointF pos = getCoordinatesForBoardPosition(model->position);
        pf->setPos(pos);
        pf->setRect(0, 0, BoardField::defaultWidthHeight, BoardField::defaultWidthHeight);
        this->pawns.append(pf);
    }
}

PawnField* BoardView::getPawnAtBoardPosition(BoardPosition bp) {
    for (auto *p : pawns) {
        if (p->getPosition().x == bp.x && p->getPosition().y == bp.y) return p;
    }
    return nullptr;
}

PawnField* BoardView::getPawnAtMousePosition(QPoint point) {
    for (auto *p : pawns) {
        QPointF ppos = p->pos();
        if (point.x() >= ppos.x() && point.x() <= ppos.x() + BoardField::defaultWidthHeight &&
            point.y() >= ppos.y() && point.y() <= ppos.y() + BoardField::defaultWidthHeight) {
            return p;
        }
    }
    return nullptr;
}

void BoardView::moveActivePawnToMousePosition(QPoint point, BasePawnModel *pawn) {
    PawnField *pf = getPawnAtBoardPosition(pawn->position);
    if (pf) {
        pf->setPos(point.x() - BoardField::defaultWidthHeight/2,
                   point.y() - BoardField::defaultWidthHeight/2);
    }
}

void BoardView::placeActivePawnAtBoardPosition(BasePawnModel *pawn, BoardPosition bp) {
    PawnField *pf = getPawnAtBoardPosition(pawn->position);
    if (!pf) return;
    QPointF pos = getCoordinatesForBoardPosition(bp);
    pf->setPos(pos);
    pf->setPosition(bp);
    pf->setZValue(0);
}

void BoardView::removePawnAtBoardPosition(BoardPosition bp) {
    PawnField *pf = getPawnAtBoardPosition(bp);
    if (pf) {
        pawns.removeOne(pf);
        delete pf;
    }
}

void BoardView::setPawnMoveCheckWarning(bool visible) {
    if (checkWarningTitleTextItem) {
        checkWarningTitleTextItem->setPlainText("CHECK!");
        checkWarningDescriptionTextItem->setPlainText("King is in check");
        checkWarningTitleTextItem->setVisible(visible);
        checkWarningDescriptionTextItem->setVisible(visible);
    }
}

void BoardView::promotePawnAtBoardPosition(BoardPosition bp) {
    PawnField *pf = getPawnAtBoardPosition(bp);
    if (pf) {
        // Determine color from position
        QString imgPath = (bp.y == 0) ? ":/Images/queen_white.svg" : ":/Images/queen_black.svg";
        pf->setImage(imgPath);
    }
}

QPointF BoardView::getCoordinatesForBoardPosition(BoardPosition pos) {
    return QPointF(25 + pos.x * BoardField::defaultWidthHeight,
                   25 + pos.y * BoardField::defaultWidthHeight);
}

// Highlight possible moves
void BoardView::highlightMoves(QList<BoardPosition> positions) {
    clearHighlights();
    for (auto &bp : positions) {
        QPointF center = getCoordinatesForBoardPosition(bp);
        QGraphicsEllipseItem *dot = new QGraphicsEllipseItem(
            center.x() + BoardField::defaultWidthHeight/2 - 12,
            center.y() + BoardField::defaultWidthHeight/2 - 12,
            24, 24, this);
        dot->setBrush(QColor(50, 200, 50, 160));
        dot->setPen(Qt::NoPen);
        dot->setZValue(2);
        highlightItems.append(dot);
    }
}

void BoardView::clearHighlights() {
    for (auto *item : highlightItems) delete item;
    highlightItems.clear();
    // Also clear selection highlights
    for (auto *field : fields) {
        bool isLight = (field->getPosition().x + field->getPosition().y) % 2 == 0;
        QColor color = isLight ? Constants::lightSquare : Constants::darkSquare;
        QBrush brush(color);
        field->setBrush(brush);
    }
}

void BoardView::highlightSelectedPawn(BoardPosition bp) {
    for (auto *field : fields) {
        if (field->getPosition().x == bp.x && field->getPosition().y == bp.y) {
            field->setBrush(QBrush(QColor(196, 160, 90, 180)));
            break;
        }
    }
}
