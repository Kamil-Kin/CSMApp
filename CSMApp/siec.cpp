#include "ziarno.h"
#include "symulacja.h"
#include "pakiet.h"
#include "siec.h"
#include "nadajnik.h"
#include "kanal.h"
#include <cstdlib>
#include <cmath>

Siec::Siec(Symulacja* sym, Ziarno* ziarno, Statystyka* stat) :opoznienie_(0.0), czas_oczekiwania_(0.0)
{
  stat_ = stat;
  sym_ = sym;
  los_czas_transmisji_ = new GenRownomierny(ziarno->PobierzZiarno(0 + sym_->NrSymulacji()*(3 + LiczbaNad())));
  los_prawdopodobienstwo_ = new GenRownomierny(ziarno->PobierzZiarno(1 + sym_->NrSymulacji()*(3 + LiczbaNad())));
  los_retransmisja_ = new GenRownomierny(ziarno->PobierzZiarno(2 + sym_->NrSymulacji()*(3 + LiczbaNad())));
  kanal_ = new Kanal();
  nadajniki_ = new vector<Nadajnik*>;
  for (int i = 0; i < kLiczbaNadajnikow; ++i)
  {
    nadajniki_->push_back(new Nadajnik(i, ziarno, sym, this, kanal_));
  }
}

Siec::~Siec()
{
  Nadajnik* nad = nullptr;
  for (int i = 0; i < kLiczbaNadajnikow; i++) 
  {
    nad = nadajniki_->back();
    nadajniki_->pop_back();
    delete nad;
  }
  delete nadajniki_;
  delete kanal_;
  delete los_czas_transmisji_;
  delete los_prawdopodobienstwo_;
  delete los_retransmisja_;
}

double Siec::LosCzasTransmisji() { return round(los_czas_transmisji_->GeneracjaR(1.0, 10.0)); }

double Siec::LosPrawdopodobienstwo()
{
  double p = los_prawdopodobienstwo_->Generacja01();
  p *= 100.0;
  p = round(p);
  p /= 100.0;
  return p;
}

double Siec::LosRetransmisja(int l_ret)
{
  double koniec = pow(2.0, l_ret) - 1.0;
  double R = los_retransmisja_->GeneracjaR(0.0, koniec);
  R *= 10.0;
  R = round(R);
  R /= 10.0;
  return R;
}

void Siec::CzyszczenieStatystyk()
{
  stat_->pakiety_wygenerowane_ = 0;
  stat_->pakiety_nadane_ = 0;
  stat_->pakiety_stracone_ = 0;
  stat_->pakiety_odebrane_ = 0;
  stat_->licznik_retransmisji_ = 0;
  stat_->sr_stopa_bledow_ = 0.0;
  stat_->max_stopa_bledow_ = 0.0;
  stat_->sr_l_ret_ = 0.0;
  stat_->sr_opoznienie_ = 0.0;
  stat_->sr_czas_oczekiwania_ = 0.0;
}

void Siec::Statystyki() 
{
  //plik.open("statystyki_raport.txt", ios::out | ios::app);
  cout << "Statystyki symulacji nr: " << sym_->NrSymulacji() << " dla lambdy: " << sym_->Lambda() << endl;
  //plik << "Statystyki symulacji nr: " << sym_->NrSymulacji() << " dla lambdy: " << sym_->Lambda() << endl;
  vector<double> stopa_bledow;
  double suma = 0;
  int l_elem = 0;
  int indeks = 0;

  //if (plik.good() == true) {
    for (int i = 0; i < kLiczbaNadajnikow; i++)
    {
      stat_->pakiety_wygenerowane_ += nadajniki_->at(i)->Generowane();
      stat_->pakiety_nadane_ += nadajniki_->at(i)->Nadane();
      stat_->pakiety_stracone_ += nadajniki_->at(i)->Stracone();
      stat_->pakiety_odebrane_ += nadajniki_->at(i)->Odebrane();
      stat_->licznik_retransmisji_ += nadajniki_->at(i)->Retransmisje();
      stopa_bledow.push_back(nadajniki_->at(i)->StopaBledow());
      suma += nadajniki_->at(i)->StopaBledow();
      cout << "Nadajnik nr " << i << ": wygenerowane: " << nadajniki_->at(i)->Generowane()
        << "; nadane: " << nadajniki_->at(i)->Nadane() << "; stracone: " << nadajniki_->at(i)->Stracone()
        << "; odebrane: " << nadajniki_->at(i)->Odebrane() << "; retransmisje: " << nadajniki_->at(i)->Retransmisje()
        << "; stopa bledow: " << nadajniki_->at(i)->StopaBledow()
        << "; srednia liczba retransmisji: " << (nadajniki_->at(i)->Retransmisje()) / static_cast<double>(nadajniki_->at(i)->Odebrane()) << endl;

      //plik << "Nadajnik nr " << i << ": wygenerowane: " << nadajniki_->at(i)->Generowane()
      //  << "; nadane: " << nadajniki_->at(i)->Nadane() << "; stracone: " << nadajniki_->at(i)->Stracone()
      //  << "; odebrane: " << nadajniki_->at(i)->Odebrane() << "; retransmisje: " << nadajniki_->at(i)->Retransmisje()
      //  << "; stopa bledow: " << nadajniki_->at(i)->StopaBledow()
      //  << "; srednia liczba retransmisji: " << (nadajniki_->at(i)->Retransmisje()) / static_cast<double>(nadajniki_->at(i)->Odebrane()) << endl;
    }
    for (int i = 0; i < kLiczbaNadajnikow; i++) 
    {
      if (stopa_bledow[i] > stat_->max_stopa_bledow_) 
      {
        stat_->max_stopa_bledow_ = stopa_bledow[i];
        indeks = i;
      }
    }
    cout << "Laczna liczba wygenerowanych pakietow: " << stat_->pakiety_wygenerowane_ << endl;
    cout << "Laczna liczba nadanych pakietow: " << stat_->pakiety_nadane_ << endl;
    cout << "Laczna liczba straconych pakietow: " << stat_->pakiety_stracone_ << endl;
    cout << "Laczna liczba odebranych pakietow: " << stat_->pakiety_odebrane_ << endl;
    l_elem = stopa_bledow.size();
    stat_->sr_stopa_bledow_ = suma / l_elem;
    cout << "Srednia pakietowa stopa bledow: " << stat_->sr_stopa_bledow_ << endl;
    cout << "Maksymalna pakietowa stopa bledow: " << stat_->max_stopa_bledow_ << "; nadajnik nr: " << indeks << endl;
    stat_->sr_l_ret_ = stat_->licznik_retransmisji_ / static_cast<double>(stat_->pakiety_odebrane_);
    cout << "Srednia liczba retransmisji pakietow (poprawnie odebranych): " << stat_->sr_l_ret_ << endl;
    stat_->przeplywnosc_ = stat_->pakiety_odebrane_ / (sym_->CzasSymulacji() / 1000);
    cout << "Przeplywnosc systemu w jednostce czasu (pakiety odebrane na sekunde): " << stat_->przeplywnosc_ << endl;
    stat_->sr_opoznienie_ = opoznienie_ / static_cast<double>(stat_->pakiety_odebrane_);
    cout << "Srednie opoznienie pakietu: " << stat_->sr_opoznienie_ << endl;
    stat_->sr_czas_oczekiwania_ = czas_oczekiwania_ / static_cast<double>(stat_->pakiety_nadane_);
    cout << "Sredni czas oczekiwania: " << stat_->sr_czas_oczekiwania_ << endl;

/*Zapisywanie do plików na rzecz statystyk i wykresów*/
    //plik << "Laczna liczba wygenerowanych pakietow: " << stat_->pakiety_wygenerowane_ << endl;
    //plik << "Laczna liczba nadanych pakietow: " << stat_->pakiety_nadane_ << endl;
    //plik << "Laczna liczba straconych pakietow: " << stat_->pakiety_stracone_ << endl;
    //plik << "Laczna liczba odebranych pakietow: " << stat_->pakiety_odebrane_ << endl;
    //plik << "Srednia pakietowa stopa bledow: " << stat_->sr_stopa_bledow_ << endl;
    //plik2.open("sr_stopy_bledow_test.txt", ios::out | ios::app);
    ////if (plik2.good() == true) {
    //  plik2 << stat_->sr_stopa_bledow_ << endl;
    //  plik2.close();
    //}
    //else cout << "Nie uzyskano dostepu do pliku" << endl;
    //plik << "Maksymalna pakietowa stopa bledow: " << stat_->max_stopa_bledow_ << "; nadajnik nr: " << indeks << endl;
    ////plik3.open("max_stopa_bledow_test.txt", ios::out | ios::app);
    //if (plik3.good()) {
    //  plik3 << stat_->max_stopa_bledow_ << endl;
    //  plik3.close();
    //}
    //else cout << "Nie uzyskano dostepu do pliku" << endl;
    //plik << "Srednia liczba retransmisji pakietow (poprawnie odebranych): " << stat_->sr_l_ret_ << endl;
    //plik << "Przeplywnosc systemu w jednostce czasu (pakiety odebrane na sekunde): " << stat_->przeplywnosc_ << endl;
    //plik4.open("przeplywnosc_test.txt", ios::out | ios::app);
    ////if (plik4.good()) {
    //  plik4 << stat_->przeplywnosc_ << endl;
    //  plik4.close();
    //}
    //else cout << "Nie uzyskano dostepu do pliku" << endl;
    //plik << "Srednie opoznienie pakietu: " << stat_->sr_opoznienie_ << endl;
    //plik << "Sredni czas oczekiwania: " << stat_->sr_czas_oczekiwania_ << endl;
    //plik.close();
  //} else cout << "Nie uzyskano dostepu do pliku" << endl;
}

void Siec::StatystykiPakietu(Pakiet* pak)
{
  //sym_->tab[pak->IdPakietu()] = pak->Opoznienie(); //do wyznaczenia fazy pocz¹tkowej
  opoznienie_ += pak->Opoznienie();
  czas_oczekiwania_ += pak->CzasWBuforze();
}
