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
  int liczba_symulacji_ = 2;
  double czas_symulacji_ = 50;
  double faza_poczatkowa_ = 900000;
  double lambda_ = 0.0067;
  char tryb_symulacji_ = 't';
  bool logi_ = true;

  Statystyka* statystyka = new Statystyka();
  Ziarno ziarno;
  ziarno.GeneracjaZiaren();

  //Histogram histogram;
  //histogram.Rownomierny();
  //histogram.Wykladniczy();

  //cout << "Ustalone parametry programu: " 
  //  << "\nliczba symulacji: " << liczba_symulacji_
  //  << "; czas jednej symulacji: " << czas_symulacji_ << " ms; " 
  //  << "faza poczatkowa: " << faza_poczatkowa_ << " ms; "
  //  << "lambda: " << lambda_ << endl;
  //
  //char param;
  //cout << "Czy uruchomic program dla nowych parametrow[T,t - tak/inny - nie]? " << endl;
  //cin >> param;

  //if (param == 'T' || param == 't') 
  //{
  //  cout << "Podaj liczbe symulacji: ";
  //  cin >> liczba_symulacji_;
  //  cout << "Podaj czas jednej symulacji [ms]: ";
  //  cin >> czas_symulacji_;
  //  cout << "Podaj dlugosc fazy poczatkowej: ";
  //  cin >> faza_poczatkowa_;
  //  cout << "Podaj wartosc lamdba: ";
  //  cin >> lambda_;
  //}
  //else
  //  cout << "Program uruchomiony dla parametrow domyslnych" << endl;
  //
  //cout << "Wybierz tryb symulacji: K,k - krokowy, inny - ciagly" << endl;
  //cin >> tryb_symulacji_;
  //
  //char log;
  //cout << "Wyswietlanie komentarzy o przebiegu transmisji pakietu[T,t - tak/inny - nie]: " << endl;
  //cin >> log;
  //if (log == 'T' || log == 't') logi_ = true;
  //else logi_ = false;

  for (int nr_symulacji = 1; nr_symulacji <= liczba_symulacji_; ++nr_symulacji) 
  {
    Symulacja* symulacja = new Symulacja(lambda_, faza_poczatkowa_, czas_symulacji_, nr_symulacji, logi_, ziarno, statystyka);
    symulacja->run(tryb_symulacji_, nr_symulacji);
    delete symulacja;
  }

  system("pause");

  return 0;
}
