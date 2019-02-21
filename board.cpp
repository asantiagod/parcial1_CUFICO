#include <cstdlib>
#include <iostream>

#include "board.h"
#include "ucrc_t.h"

using namespace std;

Board::Board(int f, int c){
    reset(f, c);
}


void Board::reset(int f, int c){
    rows = f;
    columns = c;
    board.resize(rows);
    for(int i = 0; i < board.size(); i++){
        board[i].resize(columns);
    }

    for(int f = 0; f < rows; f++){
        for(int c = 0; c < columns; c++){
            if(rand() % 2){
                board[f][c] = 1;
            }
            else
                board[f][c] = 0;
        }
    }

    uint64_t localCrc = getCrc();

    for (int i = 0; i < PERIOD; i++){
        crc[i] = localCrc;
    }
}


uint64_t Board::getCrc(){
    char msg[rows * columns];

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            msg[columns * i + j] = board[i][j];
        }
    }

    uCRC_t ucrc;
    uint64_t localCrc;

    localCrc = ucrc.get_crc_init();
    localCrc = ucrc.get_raw_crc(msg, sizeof(msg), localCrc);
    localCrc = ucrc.get_final_crc(localCrc);

    return localCrc;
}


int Board::compareCrc(){
    uint64_t localCrc = getCrc();

    uint64_t currentCrc = localCrc;
    uint64_t tempCrc;

    for (int i = 0; i < PERIOD; i++){
        if (crc[i] == localCrc)
            return 0;

        tempCrc = crc[i];
        crc[i] = currentCrc;
        currentCrc = tempCrc;
    }

    return 1;
}


void Board::draw(){
    for(int f = 0; f < rows; f++){
        for(int c = 0; c < columns; c++){
            if(board[f][c] == 1)
                cout << "* ";
            else
                cout << ". ";
        }
        cout << "\n";
    }
}


int Board::countNeighbors(int row, int column){
    int vecinos = 0;
    if(row - 1 >= 0 and column - 1 >= 0)
        if(board[row - 1][column - 1] == 1)
            vecinos++;
    if(row - 1 >= 0)
        if(board[row - 1][column] == 1)
            vecinos++;
    if(row - 1 >= 0 and column + 1 <= columns - 1)
        if(board[row - 1][column + 1] == 1)
            vecinos++;
    if(column - 1 >= 0)
        if(board[row][column - 1] == 1)
            vecinos++;
    if(column + 1 <= columns - 1)
        if(board[row][column + 1] == 1)
            vecinos++;
    if(row + 1 <= rows - 1 and column - 1 >= 0)
        if(board[row + 1][column - 1] == 1)
            vecinos++;
    if(row + 1 <= rows - 1)
        if(board[row + 1][column] == 1)
            vecinos++;
    if(row + 1 <= rows - 1 and column + 1 <= columns - 1)
        if(board[row + 1][column + 1] == 1)
            vecinos++;
    return vecinos;
}

int Board::loop(){
    vector<vector<int> > nueva_conf = board;

    for (int f = 0; f < rows; f++){
        for(int c = 0; c < columns; c++){
            int n_vecinos = countNeighbors(f, c);
            if(board[f][c] == 0){
                if(n_vecinos == 3){
                    nueva_conf[f][c] = 1;
                }else
                    nueva_conf[f][c] = 0;
            }
            if (board[f][c] == 1){
                if(n_vecinos == 2 || n_vecinos == 3){
                    nueva_conf[f][c] = 1;
                }
                else
                    nueva_conf[f][c] = 0;
            }
        }
    }

    board = nueva_conf;

    // si el crc es distinto a los de la lista es porque no hay ciclo
    if(compareCrc())
        return 1;

    return 0;
}