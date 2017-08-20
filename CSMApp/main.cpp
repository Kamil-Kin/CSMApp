#include "symulacja.h"
#include "zdarzenie.h"
#include "ziarno.h"
#include  <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() 
{ 
  double lambda;
  double faza;
  //cout << "Podaj wartosc lamdba: ";
  //cin >> lambda;
  //cout << "Podaj d³ugoœæ fazy pocz¹tkowej: ";
  //cin >> faza;
  //Symulacja symulacja(lambda, faza);

  Symulacja symulacja(0.0067, 100000);
  Ziarno ziarno;
  ziarno.GeneracjaZiaren();

  /*
  cout << "Podaj liczbe symulacji: ";
  cin >> symulacja.liczba_symulacji_;
  cout << "Podaj czas jednej symulacji [ms]: ";
  cin >> symulacja.czas_symulacji_;
  cout << "Wybierz tryb symulacji: K\k - krokowy, inny - ciagly" << endl;
  cin >> symulacja.tryb_symulacji_;*/

  for (int i = symulacja.nr_symulacji_; i < symulacja.liczba_symulacji_; ++i) 
  {
    symulacja.run(ziarno);
    symulacja.nr_symulacji_++;
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