#include <iostream>
#include <cstdlib>
#include <unistd.h>

/*-- Root --*/
#include "TH1F.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"

#include "board.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(){
    srand(time(NULL));
    Board board(20, 20);

    while(board.loop()){
        board.draw();
        cout << board.crc[0] << endl;
        cout << board.crc[1] << endl;
        usleep(100000);
        system("clear");
    }


    cout << "Ejecucion terminada" << endl;
    return 0;
}