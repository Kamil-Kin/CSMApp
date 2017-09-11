#include "histogram.h"

void Histogram::Rownomierny() 
{
  fstream plik;
  GenRownomierny* rownomierny = new GenRownomierny(1);

  plik.open("hist_rownomierny.txt", ios::out | ios::trunc);

  if (plik.good() == true) 
  {
    for (int i = 0; i < 100000; ++i)
      plik << rownomierny->Generacja01() << " ";
    plik.close();
  }
  else std::cout << "Nie uzyskano dostepu do pliku" << std::endl;
}

void Histogram::Wykladniczy() 
{
  fstream plik;
  GenWykladniczy* wykladniczy = new GenWykladniczy(0.006, 1);

  plik.open("hist_wykladniczy.txt", ios::out | ios::trunc);

  if (plik.good() == true)
  {
    for (int i = 0; i < 100000; ++i)
      plik << wykladniczy->GeneracjaW() << " ";
    plik.close();
  }
  else std::cout << "Nie uzyskano dostepu do pliku" << std::endl;
}