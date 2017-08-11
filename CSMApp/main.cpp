#include "symulacja.h"
#include "zdarzenie.h"
#include "ziarno.h"
#include  <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() 
{
  Symulacja symulacja;
  Ziarno ziarno;
  ziarno.GeneracjaZiaren();

  cout << "Podaj liczbê symulacji: ";
  cin >> symulacja.liczba_symulacji_;
  cout << "Podaj czas jednej symulacji [ms]: ";
  cin >> symulacja.czas_symulacji_;
  cout << "Wybierz tryb symulacji: K\k - krokowy, inny - ciagly" << endl;
  cin >> symulacja.tryb_symulacji_;
  for (int i = 0; i < symulacja.liczba_symulacji_; ++i) 
  {
    symulacja.run();

  }

  system("pause");
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