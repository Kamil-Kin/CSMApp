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

void Siec::StatystykiPakietu(Pakiet* pak)
{

}

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
    cout << "Nadajnik nr " << i << ": wygenerowane pakiety: " << stat_->pakiety_wygenerowane_
      << ";\npakiety transmitowane: " << stat_->pakiety_nadane_ << "; pakiety stracone: " << stat_->pakiety_stracone_
      << "; pakiety odebrane: " << stat_->pakiety_odebrane_ << ";\nliczba retransmisji: " << stat_->licznik_retransmisji_
      << "; pakietowa stopa bledow: " << nadajniki_.at(i)->StopaBledow() << endl;
  }
  l_elem = stopa_bledow_.size();
  stat_->sr_stopa_bledow_ = suma / l_elem;
  cout << "Srednia pakietowa stopa bledow: " << stat_->sr_stopa_bledow_ << endl;
  cout << "Maksymalna pakietowa stopa bledow: " << stat_->max_stopa_bledow_ << "; nadajnik nr: " << indeks << endl;
  stat_->sr_l_ret_ = stat_->licznik_retransmisji_ / kLiczbaNad_;
  cout << "Srednia liczba retransmisji pakietow (poprawnie odebranych)" << stat_->sr_l_ret_ << endl;
  stat_->przeplywnosc_ = stat_->pakiety_odebrane_ / (sym_->czas_symulacji_ / 1000);
  cout << "Przeplywnosc systemu w jednostce czasu (na sekunde): " << stat_->przeplywnosc_ << endl;

}
