#ifndef BOARD_H
#define BOARD_H

#include <vector>

using std::vector;

class Board{
public:
    int rows;
    int columns;
    int alive;
    vector<vector<int> > board;
    vector<vector<int> > board1;
    vector<vector<int> > board2;

    Board(int rows, int columns);
    void reset(int rows, int columns);
    int compareWith(int type);
    void draw();
    int countNeighbors(int row, int column);
    int loop();
};

#endif