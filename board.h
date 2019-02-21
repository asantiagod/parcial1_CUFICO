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

    // for crc code manipulation
    uint64_t crc[20];

    // initialization
    Board(int rows, int columns);
    void reset(int rows, int columns);
    
    // for crc
    uint64_t getCrc();

    // for loop
    int compareCrc();
    void draw();
    int countNeighbors(int row, int column);
    int loop();
};

#endif