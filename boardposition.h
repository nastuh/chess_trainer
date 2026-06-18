#ifndef BOARDPOSITION_H
#define BOARDPOSITION_H

struct BoardPosition {
    int x;
    int y;
};

class PawnPosition {
public:
    PawnPosition(int x, int y);
    int x;
    int y;
};

#endif // BOARDPOSITION_H
