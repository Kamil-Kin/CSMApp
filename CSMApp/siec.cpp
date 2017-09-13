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
  los_czas_transmisji_ = new GenRownomierny(ziarno->PobierzZiarno(0 + sym_->nr_symulacji_*(3 + LiczbaNad())));
  los_prawdopodobienstwo_ = new GenRownomierny(ziarno->PobierzZiarno(1 + sym_->nr_symulacji_*(3 + LiczbaNad())));
  los_retransmisja_ = new GenRownomierny(ziarno->PobierzZiarno(2 + sym_->nr_symulacji_*(3 + LiczbaNad())));
  kanal_ = new Kanal();
  nadajniki_ = new vector<Nadajnik*>;
  for (int i = 0; i < kLiczbaNadajnikow; ++i)
  {
    nadajniki_->push_back(new Nadajnik(i, ziarno, sym_, this, kanal_));//680B
  }
}
Siec::~Siec()
{
  delete kanal_;
  //nadajniki_->erase(nadajniki_->begin(), nadajniki_->end());
  //Nadajnik* nad = nullptr;
  //for (int i = 0; i < kLiczbaNadajnikow; i++) 
  //{
  //  nad = nadajniki_->back();
  //  nadajniki_->pop_back();
  //  delete nad;
  //}
  delete nadajniki_;
  //delete los_czas_transmisji_;
  //delete los_prawdopodobienstwo_;
  //delete los_retransmisja_;
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

double Siec::LosRetransmisja(int l_ret_)
{
  double koniec = pow(2.0, l_ret_) - 1.0;
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
  //plik.open("statystyki.txt", ios::out | ios::app);
  //sym_->UstawKolor("07");
  cout << "Statystyki symulacji nr: " << sym_->nr_symulacji_ << endl;
  //plik << "Statystyki symulacji nr: " << sym_->nr_symulacji_ << endl;
  vector<double> stopa_bledow_;
  double suma = 0;
  int l_elem = 0;
  int indeks = 0;

  //if (plik.good() == true) 
  //{
    for (int i = 0; i < kLiczbaNadajnikow; i++)
    {
      stat_->pakiety_wygenerowane_ += nadajniki_->at(i)->licznik_pakietow_;
      stat_->pakiety_nadane_ += nadajniki_->at(i)->licznik_nadanych_;
      stat_->pakiety_stracone_ += nadajniki_->at(i)->licznik_straconych_;
      stat_->pakiety_odebrane_ += nadajniki_->at(i)->licznik_odebranych_;
      stat_->licznik_retransmisji_ += nadajniki_->at(i)->licznik_retransmisji_;
      stopa_bledow_.push_back(nadajniki_->at(i)->StopaBledow());
      suma += nadajniki_->at(i)->StopaBledow();
      cout << "Nadajnik nr " << i << ": wygenerowane: " << nadajniki_->at(i)->licznik_pakietow_
        << "; nadane: " << nadajniki_->at(i)->licznik_nadanych_ << "; stracone: " << nadajniki_->at(i)->licznik_straconych_
        << "; odebrane: " << nadajniki_->at(i)->licznik_odebranych_ << "; retransmisje: " << nadajniki_->at(i)->licznik_retransmisji_
        << "; stopa bledow: " << nadajniki_->at(i)->StopaBledow()
        << "; srednia liczba retransmisji: " << (nadajniki_->at(i)->licznik_retransmisji_) / static_cast<double>(nadajniki_->at(i)->licznik_odebranych_) << endl;
      //plik << "Nadajnik nr " << i << ": wygenerowane: " << nadajniki_->at(i)->licznik_pakietow_
      //  << "; nadane: " << nadajniki_->at(i)->licznik_nadanych_ << "; stracone: " << nadajniki_->at(i)->licznik_straconych_
      //  << "; odebrane: " << nadajniki_->at(i)->licznik_odebranych_ << "; retransmisje: " << nadajniki_->at(i)->licznik_retransmisji_
      //  << "; stopa bledow: " << nadajniki_->at(i)->StopaBledow()
      //  << "; srednia liczba retransmisji: " << (nadajniki_->at(i)->licznik_retransmisji_) / static_cast<double>(nadajniki_->at(i)->licznik_odebranych_) << endl;
    }
    for (int i = 0; i < kLiczbaNadajnikow; i++) 
    {
      if (stopa_bledow_[i] > stat_->max_stopa_bledow_) 
      {
        stat_->max_stopa_bledow_ = stopa_bledow_[i];
        indeks = i;
      }
    }
    cout << "Laczna liczba wygenerowanych pakietow: " << stat_->pakiety_wygenerowane_ << endl;
    //plik << "Laczna liczba wygenerowanych pakietow: " << stat_->pakiety_wygenerowane_ << endl;
    cout << "Laczna liczba nadanych pakietow: " << stat_->pakiety_nadane_ << endl;
    //plik << "Laczna liczba nadanych pakietow: " << stat_->pakiety_nadane_ << endl;
    cout << "Laczna liczba straconych pakietow: " << stat_->pakiety_stracone_ << endl;
    //plik << "Laczna liczba straconych pakietow: " << stat_->pakiety_stracone_ << endl;
    cout << "Laczna liczba odebranych pakietow: " << stat_->pakiety_odebrane_ << endl;
    //plik << "Laczna liczba odebranych pakietow: " << stat_->pakiety_odebrane_ << endl;

    l_elem = stopa_bledow_.size();
    stat_->sr_stopa_bledow_ = suma / l_elem;
    plik2.open("sr_stopy_bledow.txt", ios::out | ios::app); //todo
    if (plik2.good() == true) {
      plik2 << stat_->sr_stopa_bledow_ << " ";
      plik2.close();
    }
    else cout << "Nie uzyskano dostepu do pliku" << endl;

    cout << "Srednia pakietowa stopa bledow: " << stat_->sr_stopa_bledow_ << endl;
    //plik << "Srednia pakietowa stopa bledow: " << stat_->sr_stopa_bledow_ << endl;
    cout << "Maksymalna pakietowa stopa bledow: " << stat_->max_stopa_bledow_ << "; nadajnik nr: " << indeks << endl;
    //plik << "Maksymalna pakietowa stopa bledow: " << stat_->max_stopa_bledow_ << "; nadajnik nr: " << indeks << endl;

    stat_->sr_l_ret_ = stat_->licznik_retransmisji_ / static_cast<double>(stat_->pakiety_odebrane_);
    cout << "Srednia liczba retransmisji pakietow (poprawnie odebranych): " << stat_->sr_l_ret_ << endl;
    //plik << "Srednia liczba retransmisji pakietow (poprawnie odebranych): " << stat_->sr_l_ret_ << endl;

    stat_->przeplywnosc_ = stat_->pakiety_odebrane_ / (sym_->czas_symulacji_ / 1000);
    cout << "Przeplywnosc systemu w jednostce czasu (pakiety odebrane na sekunde): " << stat_->przeplywnosc_ << endl;
    //plik << "Przeplywnosc systemu w jednostce czasu (pakiety odebrane na sekunde): " << stat_->przeplywnosc_ << endl;
    
    stat_->sr_opoznienie_ = opoznienie_ / static_cast<double>(stat_->pakiety_odebrane_);  //todo
    cout << "Srednie opoznienie pakietu: " << stat_->sr_opoznienie_ << endl;
    //plik << "Srednie opoznienie pakietu: " << stat_->sr_opoznienie_ << endl;

    stat_->sr_czas_oczekiwania_ = czas_oczekiwania_ / static_cast<double>(stat_->pakiety_nadane_);  //todo
    cout << "Sredni czas oczekiwania: " << stat_->sr_czas_oczekiwania_ << endl;
    //plik << "Sredni czas oczekiwania: " << stat_->sr_czas_oczekiwania_ << endl;

    //plik.close();
  //}
  //else cout << "Nie uzyskano dostepu do pliku" << endl;
}

void Siec::StatystykiPakietu(Pakiet* pak)
{
  //sym_->tab[pak->id_] = pak->opoznienie_pakietu_; //do wyznaczenia fazy pocz¹tkowej
  opoznienie_ += pak->opoznienie_pakietu_;
  czas_oczekiwania_ += pak->czas_w_buforze_;
}
