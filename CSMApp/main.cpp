#include "statystyka.h"
#include "histogram.h"
#include "symulacja.h"
#include "zdarzenie.h"
#include "logi.h"
#include "ziarno.h"
#include  <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
  int liczba_symulacji_ = 10;
  double czas_symulacji_ = 50000; //w milisekundach; 50 sekund
  int faza_poczatkowa_ = 25;  //mierzone w ilo�ci pakiet�w
  double lambda_ = 0.0031;
  char tryb_symulacji_ = 't';
  bool logi_ = false;

  Statystyka* statystyka = new Statystyka();
  Logi* ptr_logi = new Logi();
  Ziarno* ziarno = new Ziarno();
  ziarno->GeneracjaZiaren();

  //Generacja histogram�w
  //Histogram histogram;
  //histogram.Rownomierny();
  //histogram.Wykladniczy();

  cout << "Ustalone parametry programu: " << "\nliczba symulacji: " << liczba_symulacji_
    << "; czas jednej symulacji: " << czas_symulacji_ << " ms; "
    << "faza poczatkowa: " << faza_poczatkowa_ << " pakietow; " << "lambda: " << lambda_
    << "\nWylaczone komentarze oraz ciagly tryb symulacji" << endl;

  char param;
  cout << "Czy uruchomic program dla nowych parametrow[T,t - tak/inny - nie]? " << endl;
  cin >> param;

  if (param == 'T' || param == 't') 
  {
    cout << "Podaj liczbe symulacji: ";
    cin >> liczba_symulacji_;
    cout << "Podaj czas jednej symulacji [ms]: ";
    cin >> czas_symulacji_;
    cout << "Podaj dlugosc fazy poczatkowej(ilosc pakietow): ";
    cin >> faza_poczatkowa_;
    cout << "Podaj wartosc lamdba: ";
    cin >> lambda_;
  }
  else
    cout << "Program uruchomiony dla parametrow domyslnych" << endl;

  char log;
  cout << "Wyswietlanie komentarzy o przebiegu transmisji pakietu[T,t - tak/inny - nie]: " << endl;
  cin >> log;
  if (log == 'T' || log == 't') logi_ = true;
  else logi_ = false;

  cout << "Wybierz tryb symulacji[K,k - krokowy, inny - ciagly]: " << endl;
  cin >> tryb_symulacji_;

  Symulacja* symulacja = nullptr;

  for (int nr_symulacji = 1; nr_symulacji <= liczba_symulacji_; ++nr_symulacji) 
  {
    symulacja = new Symulacja(lambda_, faza_poczatkowa_, czas_symulacji_, nr_symulacji, logi_, ptr_logi, ziarno, statystyka);
    symulacja->run(tryb_symulacji_, nr_symulacji); 
    delete symulacja;
  }
  delete statystyka;
  delete ptr_logi;
  delete ziarno;

  system("pause");

  return 0;
}
