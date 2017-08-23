#include "ziarno.h"
#include "symulacja.h"
#include "pakiet.h"
#include "siec.h"
#include "nadajnik.h"
#include "kanal.h"
#include <cstdlib>
#include <ctime>

Siec::Siec(Symulacja* sym, Ziarno ziarno, Statystyka* stat) 
{
  srand(time(NULL));
  stat_ = stat;
  sym_ = sym;
  kanal_ = new Kanal();
  for (int i = 0; i < kLiczbaNad_; i++)
  {
    nadajniki_.push_back(new Nadajnik(i, ziarno, sym_, this, kanal_));
  }
}
Siec::~Siec() {}

void Siec::Statystyki() 
{
  vector<double> stopa_bledow_;
  double suma = 0;
  int l_elem = 0;
  int indeks = 0;
  for (int i = 0; i < kLiczbaNad_; i++) 
  {
    stat_->pakiety_wygenerowane_ += nadajniki_.at(i)->licznik_pakietow_;
    stat_->pakiety_nadane_ += nadajniki_.at(i)->licznik_nadanych_;
    stat_->pakiety_stracone_ += nadajniki_.at(i)->licznik_straconych_;
    stat_->pakiety_odebrane_ += nadajniki_.at(i)->licznik_odebranych_;
    stat_->licznik_retransmisji_ += nadajniki_.at(i)->licznik_ret_;
    stopa_bledow_.push_back(nadajniki_.at(i)->StopaBledow());
    suma += stopa_bledow_[i];
    stat_->max_stopa_bledow_ = stopa_bledow_[i];
    if (stopa_bledow_[i] > stat_->max_stopa_bledow_) 
    {
      stat_->max_stopa_bledow_ = stopa_bledow_[i];
      indeks++;
    }
    cout << "Nadajnik nr " << i << ": wygenerowane pakiety: " << nadajniki_.at(i)->licznik_pakietow_
      << ";\npakiety transmitowane: " << nadajniki_.at(i)->licznik_nadanych_ << "; pakiety stracone: " << nadajniki_.at(i)->licznik_straconych_
      << "; pakiety odebrane: " << nadajniki_.at(i)->licznik_odebranych_ << ";\nliczba retransmisji: " << nadajniki_.at(i)->licznik_ret_
      << "; pakietowa stopa bledow: " << nadajniki_.at(i)->StopaBledow() << endl;
  }
  cout << "Laczna liczba wygenerowanych pakietow: " << stat_->pakiety_wygenerowane_ << endl;
  cout << "Laczna liczba nadanych pakietow: " << stat_->pakiety_nadane_ << endl;
  cout << "Laczna liczba straconych pakietow: " << stat_->pakiety_stracone_ << endl;
  cout << "Laczna liczba odebranych pakietow: " << stat_->pakiety_odebrane_ << endl;
  l_elem = stopa_bledow_.size();
  stat_->sr_stopa_bledow_ = suma / l_elem;
  cout << "Srednia pakietowa stopa bledow: " << stat_->sr_stopa_bledow_ << endl;
  cout << "Maksymalna pakietowa stopa bledow: " << stat_->max_stopa_bledow_ << "; nadajnik nr: " << indeks << endl;
  stat_->sr_l_ret_ = stat_->licznik_retransmisji_ / kLiczbaNad_;
  cout << "Srednia liczba retransmisji pakietow (poprawnie odebranych)" << stat_->sr_l_ret_ << endl;
  stat_->przeplywnosc_ = stat_->pakiety_odebrane_ / (sym_->czas_symulacji_ / 1000);
  cout << "Przeplywnosc systemu w jednostce czasu (na sekunde): " << stat_->przeplywnosc_ << endl;
  cout << "Srednie opoznienie pakietu: " << opoznienie_ << endl;
  cout << "Sredni czas oczekiwania: " << czas_oczekiwania_ << endl;
}

void Siec::StatystykiPakietu(Pakiet* pak)
{
  opoznienie_ += pak->opoznienie_pakietu_;
  czas_oczekiwania_ += pak->czas_w_buforze_;
}