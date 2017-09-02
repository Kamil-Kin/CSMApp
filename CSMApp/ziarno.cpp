#include "ziarno.h"

Ziarno::Ziarno() :odstep_ziaren_(100000), liczba_ziaren_(200) 
{
  uniform_ = new GenRownomierny(1);
}
Ziarno::~Ziarno() {}

void Ziarno::GeneracjaZiaren() 
{
  fstream plik;
  int temp;
  plik.open("ziarno.txt", ios::in | ios::out);

  if (plik.good() == true) 
  {
    for (int i = 0; i < liczba_ziaren_; ++i) 
    {
      for (int j = 0; j < odstep_ziaren_; ++j) 
        uniform_->Generacja01();
      temp = uniform_->getKernel();
      plik << temp << endl;
      //plik << endl;
      ziarna[i] = temp;
    }
    plik.close();
  }
  else cout << "Nie uzyskano dostepu do pliku" << endl;
}

int Ziarno::PobierzZiarno(int index)
{
  //cout << "ziarno nr: " << index << "\twartosc: " << ziarna[index] << endl;
  return ziarna[index];
}
