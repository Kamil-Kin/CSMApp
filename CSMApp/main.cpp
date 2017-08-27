#include "statystyka.h"
#include "histogram.h"
#include "symulacja.h"
#include "zdarzenie.h"
#include "ziarno.h"
#include  <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() 
{
  Statystyka* statystyka = new Statystyka();
  Histogram histogram;
  histogram.Rownomierny();
  histogram.Wykladniczy();
  Symulacja symulacja(0.0068, 900000);
  Ziarno ziarno;
  ziarno.GeneracjaZiaren();

  char param;
  cout << "Ustalone parametry programu: " << "\nliczba symulacji: " << symulacja.liczba_symulacji_
    << "; czas jednej symulacji: " << symulacja.czas_symulacji_ << " ms; " << "faza poczatkowa: " << symulacja.faza_poczatkowa_ << " ms; "
    << "lambda: " << symulacja.lambda_ << endl;
  cout << "Czy uruchomic program dla nowych parametrow[T,t - tak/inny - nie]? " << endl;
  cin >> param;
  cout << "Wybierz tryb symulacji: K,k - krokowy, inny - ciagly" << endl;
  cin >> symulacja.tryb_symulacji_;

  if (param == 'T' || param == 't') 
  {
    cout << "Podaj liczbe symulacji: ";
    cin >> symulacja.liczba_symulacji_;
    cout << "Podaj czas jednej symulacji [ms]: ";
    cin >> symulacja.czas_symulacji_;
    double lambda = 0;
    cout << "Podaj wartosc lamdba: ";
    cin >> lambda;
    double faza = 0;
    cout << "Podaj dlugosc fazy poczatkowej: ";
    cin >> faza;
    Symulacja symulacja(lambda, faza);
  }
  else
  {
    cout << "Program uruchomiony dla parametrow domyslnych" << endl;
  }

  for (int i = symulacja.nr_symulacji_; i < symulacja.liczba_symulacji_; ++i) 
  {
    symulacja.run(ziarno, statystyka);
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