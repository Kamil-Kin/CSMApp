#include "symulacja.h"
//#include  <iostream> //do testowania

int main() 
{
  Symulacja symulacja;
  symulacja.run();
  /*Zdarzenie *T = new Zdarzenie(21.0);
  symulacja.DodajDoKalendarza(T);
  Zdarzenie *T1 = new Zdarzenie(11.0);
  symulacja.DodajDoKalendarza(T1);
  std::cout << (symulacja.PobierzPierwszyElement())->pobierz_czas_zd() << std::endl;
  symulacja.UsunZKalendarza();
  std::cout << (symulacja.PobierzPierwszyElement())->pobierz_czas_zd() << std::endl;*/ //testowanie
  system("pause");
  return 0;
}