#include <iostream>
#include <cstdlib>
#include <unistd.h>

/*-- Root --*/
#include "TH1F.h"
#include "TCanvas.h"
#include "TF1.h"

/*
 * Se usarán numeros CRC (cyclic redundancy check) para 
 * diferenciar entre el estado de varios boards y determinar 
 * si se ha llegado a un punto estable
 */
#include "ucrc_t.h"

#include "board.h"

using namespace std;

int main(){
    uCRC_t ucrc;
    
    int len_i;  // Tamaño inicial
    int len_f;  // Tamaño final
    int step;   // Incremento    
    // TH1F fData = TH1F("h1","Histograma 1", 10, 0, 30);
    TCanvas c1("c1","Canvas 1",700,900);
    char hName[100];

    // para hacer el fit y extraer los parametros
    TF1 *fit = new TF1("fit","gaus");

    srand(time(NULL));


    cout << endl << "Ingrese el tamaño inicial o -1 para terminar" << endl;   
    cin >> len_i;
    if(len_i < 1)
        return -1;

    cout << endl << "Ingrese el tamaño final o -1 para terminar" << endl; 
    cin >> len_f;
    if(len_f < len_i)
        return -1;

    cout << endl << "Ingrese incremento o -1 para terminar" << endl;  
    cin >> step;
    if(step < 1)
        return -1;

    int maxValues[(int) (len_f - len_i) / step] = {0};
    Float_t mean[(int) (len_f - len_i) / step];
    for(int len = len_i; len <= len_f; len += step){
        // fData.Clear();
        TH1F fData = TH1F("h1","Histograma 1", 10, 0, 30);
        for(int i = 0; i < 20; i++){
            int time = 0;
            Board board(len, len);
            while(board.loop()){
                // board.draw();
                // usleep(100000);
                // system("clear");
                time++;
            }
            // system("clear");
            // cout << time << endl;
            usleep(100000);
            fData.Fill(time);
            if(time > maxValues[(len - len_i) / step])
                maxValues[(len - len_i) / step] = time;
        }
        sprintf(hName, "n = %d", len);
        fData.SetTitle(hName);
        fData.Fit(fit);
        mean[(len - len_i) / step] = fit->GetParameter(2);
        fData.Draw();

        sprintf(hName, "./img/fig%d.png", len);
        c1.SaveAs(hName);
    }

    cout << "Valores maximos y medias para cada n" << endl;
    for(int i = 0; i < (int) (len_f - len_i) / step + 1; i++)
        cout << maxValues[i] << " " << mean[i] << endl;
    
    cout << "Ejecucion terminada" << endl;
    return 0;
}