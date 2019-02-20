#include <cstdlib>
#include <iostream>

#include "board.h"

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

    alive = 0;
    for(int f = 0; f < rows; f++){
        for(int c = 0; c < columns; c++){
            if(rand() % 2){
                board[f][c] = 1;
                alive++;
            }
            else
                board[f][c] = 0;
        }
    }

    board1 = board;
    board2 = board;
}


int Board::compareWith(int tipo){
    vector<vector<int> > copia;

    if(tipo == 1)
        copia = board1;
    else
        copia = board2;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(copia[i][j] != board[i][j])
                return 0;
        }
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
    cout << alive << "\n";
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
    int aliveTemp = 0;

    for (int f = 0; f < rows; f++){
        for(int c = 0; c < columns; c++){
            int n_vecinos = countNeighbors(f, c);
            if(board[f][c] == 0){
                if(n_vecinos == 3){
                    nueva_conf[f][c] = 1;
                    aliveTemp++;
                }else
                    nueva_conf[f][c] = 0;
            }
            if (board[f][c] == 1){
                if(n_vecinos == 2 || n_vecinos == 3){
                    nueva_conf[f][c] = 1;
                    aliveTemp++;
                }
                else
                    nueva_conf[f][c] = 0;
            }
        }
    }


    board = nueva_conf;

    if(not alive)
      return 0;
    if(compareWith(1) || compareWith(2)){
        board2 = board1;
        board1 = board;
        return 1;
    }if(alive != aliveTemp){
        alive = aliveTemp;
        return 1;
    }

    return 0;
}