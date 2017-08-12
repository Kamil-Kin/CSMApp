#include "ziarno.h"

void Ziarno::GeneracjaZiaren() 
{
  std::fstream plik;
  int temp;
  plik.open("ziarno.txt", std::ios::in | std::ios::out);

  if (plik.good() == true) 
  {
    for (int i = 0; i < liczba_ziaren_; ++i) 
    {
      for (int j = 0; j < odstep_ziaren_; ++j) 
        uniform_->Generacja01();
      temp = uniform_->getKernel();
      plik << temp;
      plik << std::endl;
      ziarna[i] = temp;
    }
    plik.close();
  }
  else std::cout << "Nie uzyskano dostepu do pliku" << std::endl;
}
