#include "symulacja.h"
#include "siec.h"
#include "nadajnik.h"
#include "pakiet.h"

bool comparer::operator()(const Zdarzenie* zd1, const Zdarzenie* zd2) const
{
  if (zd1->czas_zdarzenia_ != zd2->czas_zdarzenia_)
  {
    return (zd1->czas_zdarzenia_ > zd2->czas_zdarzenia_);
  }
  return zd1->priorytet_ > zd2->priorytet_;
}

Symulacja::Symulacja(double lam, int faza, double czas, int nr, bool logi, Logi* ptr_logi, Ziarno* ziarno, Statystyka* stat) :zegar_(0.0), nr_odbioru_(0)
{
  licznik_pakietow_ = 0;
  lambda_ = lam;
  faza_poczatkowa_ = faza;
  czas_symulacji_ = czas;
  nr_symulacji_ = nr;
  log_ = logi;
  kalendarz_ = new priority_queue<Zdarzenie*, vector<Zdarzenie*>, comparer>;
  siec_ = new Siec(this, ziarno, stat);
  ptr_logi_ = ptr_logi;
  //do wyznaczenia fazy pocz¹tkowej
  //opoznienie = "opoznienie" + to_string(nr) + ".txt"; 
  //plik.open(opoznienie.c_str(), ios::out | ios::app);
}

Symulacja::~Symulacja()
{
  Zdarzenie* zd = nullptr;
  for (int i = 0; i < kalendarz_->size(); i++) 
  {
    zd = kalendarz_->top();
    kalendarz_->pop();
    delete zd;
  }
  delete kalendarz_;
  delete siec_;
  //plik.close(); //do wyznaczenia fazy pocz¹tkowej
}

void Symulacja::run(char tryb_symulacji, int nr_symulacji)
{
  cout << "\nNUMER SYMULACJI: " << nr_symulacji << endl;
  Pakiet* obecny_ = nullptr;
  while (zegar_ < czas_symulacji_)
  {
    obecny_ = kalendarz_->top()->pakiet_;
    zegar_ = kalendarz_->top()->czas_zdarzenia_;
    UsunZKalendarza();

    if (log_ == true) cout << "\nPakiet id " << obecny_->IdPakietu() << ": Pobrano z kalendarza zdarzenie o czasie: " << zegar_ << " ms";

    obecny_->execute(log_);
    if ((obecny_->Skonczony()) == true)
    {
      if (log_ == true) cout << "Pakiet id " << obecny_->IdPakietu() << ":\tusuniety z systemu" << endl;
      siec_->StatystykiPakietu(obecny_);
      delete obecny_;
    }
    if (tryb_symulacji == 'K' || tryb_symulacji == 'k') system("pause");
  }
  //do wyznaczenia fazy pocz¹tkowej
  //if (plik.good() == true) {
  //  for (int i = 0; i < 100; i++)
  //    plik << tab[i] << " ";
  //} else cout << "Nie uzyskano dostepu do pliku " << endl;
  siec_->Statystyki();
  siec_->CzyszczenieStatystyk();
}

void Symulacja::DodajDoKalendarza(Zdarzenie* zd) { kalendarz_->push(zd); }

void Symulacja::UsunZKalendarza()
{
  assert(!kalendarz_->empty());
  if (kalendarz_->empty() == false) kalendarz_->pop();
}
