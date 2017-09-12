#include "ziarno.h"

Ziarno::Ziarno() :odstep_ziaren_(100000), liczba_ziaren_(150)
{
  uniform_ = new GenRownomierny(1);
}
Ziarno::~Ziarno() {
//  delete uniform_;
}

void Ziarno::GeneracjaZiaren()
{
  //fstream plik;
  //plik.open("ziarno.txt", ios::in | ios::out | ios::trunc);
  int temp;
  //if (plik.good() == true) {
    for (int i = 0; i < liczba_ziaren_; ++i) 
    {
      for (int j = 0; j < odstep_ziaren_; ++j) 
        uniform_->Generacja01();
      temp = uniform_->getKernel();
      ziarna[i] = temp;
      //plik << temp << endl;
    }
    //plik.close();
  //}
  //else cout << "Nie uzyskano dostepu do pliku" << endl;
}

void Ziarno::PobierzZiarnoZPliku()
{
  fstream plik;
  plik.open("ziarno.txt", ios::in);
  if (plik.good() == true) 
  {
    for (int i = 0; i < liczba_ziaren_; i++)
      plik >> ziarna[i];
    plik.close();
  }
  else cout << "Nie uzyskano dostepu do pliku" << endl;
}

int Ziarno::PobierzZiarno(int index) { return ziarna[index]; }
