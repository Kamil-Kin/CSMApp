#include "ziarno.h"

void Ziarno::GeneracjaZiaren() 
{
  std::fstream plik;
  plik.open("ziarno.txt", std::ios::in | std::ios::out);

  if (plik.good() == true) 
  {
    for (int i = 0; i < liczba_ziaren_; ++i) 
    {
      for (int j = 0; j < odstep_ziaren_; ++j) 
        uniform_->Generacja01();
      plik << uniform_->getKernel();
      plik << std::endl;
    }
    plik.close();
  }
  else std::cout << "Nie uzyskano dostepu do pliku" << std::endl;
}
