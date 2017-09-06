#include "logi.h"

void Logi::WypiszLogi(int faza, int id, double zegar) 
{
  fstream plik;
  plik.open("logi.txt", ios::out);

  if (plik.good() == true) 
  {

    plik.close();
  }
  else cout << "Nie uzyskano dostepu do pliku" << endl;
}