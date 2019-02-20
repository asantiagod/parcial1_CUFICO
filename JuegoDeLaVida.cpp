#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>

/*-- Root --*/
#include "TH1F.h"
#include "TCanvas.h"

using namespace std;

class Mapa{
public:
  int fil;
  int col;
  int vivos;
  int age = 0;
  vector<vector<int> > mapa;
  
  Mapa(int f, int c);
  void reset(int f, int c);
  void dibujar();
  int analizarVecinos(int posf, int posc);
  int ciclo();
};


Mapa::Mapa(int f, int c){
  reset(f, c);
}


void Mapa::reset(int f, int c){
  fil = f;
  col = c;
  mapa.resize(fil);
  for(int i=0; i<mapa.size(); i++){
    mapa[i].resize(col);
  }
  vivos = 0;
  for(int f=0; f<fil; f++){
    for(int c=0; c<col; c++){
      if (rand()%2){
        mapa[f][c] = 1;
        vivos++;
      }
    }
  }
}


void Mapa::dibujar(){
  for(int f=0; f<fil; f++){
    for(int c=0; c<col; c++){
        if(mapa[f][c] == 1)
          cout << "* ";
        else
          cout << ". ";
    }
    cout << "\n";
  }
  cout << age << " " << vivos << "\n";
}


int Mapa::analizarVecinos(int posf, int posc)
{
  int vecinos = 0;
  if(posf-1 >= 0 and posc-1 >= 0)
    if(mapa[posf-1][posc-1] == 1)
      vecinos++;
  if(posf-1 >= 0)
    if(mapa[posf-1][posc] == 1)
      vecinos++;
  if(posf-1 >= 0 and posc+1 <= col-1)
    if(mapa[posf-1][posc+1] == 1)
      vecinos++;
  if(posc-1 >= 0)
    if(mapa[posf][posc-1] == 1)
      vecinos++;
  if(posc+1 <= col-1)
    if(mapa[posf][posc+1] == 1)
      vecinos++;
  if(posf+1 <= fil-1 and posc-1 >= 0)
    if(mapa[posf+1][posc-1] == 1)
      vecinos++;
  if(posf+1 <= fil-1)
    if(mapa[posf+1][posc] == 1)
      vecinos++;
  if(posf+1 <= fil-1 and posc+1 <= col-1)
    if(mapa[posf+1][posc+1] == 1)
      vecinos++;
  return vecinos;
}

int Mapa::ciclo(){
  vector<vector<int> > nueva_conf = mapa;
  int vivosTemp = 0;

  for (int f=0; f<fil; f++){
    for(int c=0; c<col; c++){
        int n_vecinos = analizarVecinos(f, c);
        if(mapa[f][c] == 0){
          if(n_vecinos == 3){
              nueva_conf[f][c] = 1;
          vivosTemp++;
        }
          else
              nueva_conf[f][c] = 0;
      }
        if (mapa[f][c] == 1){
          if(n_vecinos == 2 || n_vecinos == 3){
              nueva_conf[f][c] = 1;
          vivosTemp++;
        }
          else
              nueva_conf[f][c] = 0;
      }
    }
  }

  if(vivos != vivosTemp){
    mapa = nueva_conf;
    vivos = vivosTemp;
    age++;
    return 1;
  }

  return 0;
}


int main()
{
    int len_i; //Tamaño inicial
    int len_f; //Tamaño final
    int step;  //Incremento    
    TH1F fData = TH1F("h1","Histograma 1", 10, 0, 30);
    TCanvas c1("c1","Canvas 1",700,900);
    char hName[100];

    srand(time(NULL));


    cout<<endl<<"Ingrese el tamaño inicial o -1 para terminar"<<endl;   
    cin>>len_i;
    if(len_i < 1)
        return -1;

    cout<<endl<<"Ingrese el tamaño final o -1 para terminar"<<endl; 
    cin>>len_f;
    if(len_f < len_i)
        return -1;

    cout<<endl<<"Ingrese incremento o -1 para terminar"<<endl;  
    cin>>step;
    if(step < 1)
        return -1;


    for(int len=len_i; len<=len_f; len += step)
    {
        fData.Clear();
        for(int i = 0; i<500; i++)
        {
            int time = 0;            
            Mapa mapa(len, len);
            while(mapa.ciclo())
            {
                mapa.dibujar();
                usleep(100000);
                system("clear");
                time++;
            }
            fData.Fill(time);
        }
        sprintf(hName,"n = %d",len);
        fData.SetTitle(hName);
        fData.Draw();
        sprintf(hName,"./img/fig%d.png",len);
        c1.SaveAs(hName);
    }
    cout<<"Ejecucion terminada"<<endl;
    return 0;
}
