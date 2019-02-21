#ifndef BOARD_H
#define BOARD_H

#include <vector>

#define PERIOD 20

using std::vector;

class Board{
public:
    int rows;
    int columns;
    vector<vector<int> > board;

    // for crc code manipulation
    uint64_t crc[PERIOD];

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