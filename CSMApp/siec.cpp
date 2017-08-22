#include "ziarno.h"
#include "symulacja.h"
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
  list<double> stopa_bledow_;
  for (int i = 0; i < kLiczbaNad_; i++) 
  {
    stat_->pakiety_wygenerowane_ += nadajniki_.at(i)->licznik_pakietow_;
    stat_->pakiety_nadane_ += nadajniki_.at(i)->licznik_nadanych_;
    stat_->pakiety_stracone_ += nadajniki_.at(i)->licznik_straconych_;
    stat_->pakiety_odebrane_ += nadajniki_.at(i)->licznik_odebranych_;
    stat_->licznik_retransmisji_ += nadajniki_.at(i)->licznik_ret_;
    
    stopa_bledow_.push_front(nadajniki_.at(i)->StopaBledow());
    cout << "Nadajnik nr " << i << ": wygenerowane pakiety: " << stat_->pakiety_wygenerowane_
      << ";\npakiety transmitowane: " << stat_->pakiety_nadane_ << "; pakiety stracone: " << stat_->pakiety_stracone_
      << "; pakiety odebrane: " << stat_->pakiety_odebrane_ << ";\nliczba retransmisji: " << stat_->licznik_retransmisji_ << endl;
  }
  //double suma;
  //for (int i = 0; i < kLiczbaNad_; i++) 
  //{
  //  suma += stopa_bledow_.front();
  //  stopa_bledow_.pop_front();
  //}

}