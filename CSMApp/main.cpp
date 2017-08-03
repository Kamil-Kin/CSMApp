#include "symulacja.h"
#include "zdarzenie.h"
#include  <iostream> //do testowania

int main() 
{
  Symulacja symulacja;
  symulacja.run();
  //Zdarzenie *T = new Zdarzenie(21.0);
  //symulacja.DodajDoKalendarza(T);
  //Zdarzenie *T1 = new Zdarzenie(11.0);
  //symulacja.DodajDoKalendarza(T1);
  //std::cout << (symulacja.PobierzPierwszyElement())->PobierzCzasZd() << std::endl;
  //symulacja.UsunZKalendarza();
  //std::cout << (symulacja.PobierzPierwszyElement())->PobierzCzasZd() << std::endl; //testowanie
  //system("pause");
  return 0;
}