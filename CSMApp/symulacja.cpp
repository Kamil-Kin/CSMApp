#include "symulacja.h"
#include "siec.h"
#include "nadajnik.h"
//#include "pakiet.h"
#include "zdarzenie.h"
#include <iostream>
using std::cout;
using std::endl;

bool comparer::operator()(const Zdarzenie* z1, const Zdarzenie* z2) const
{
  return z1->PobierzCzasZd() > z2->PobierzCzasZd();
}

Symulacja::Symulacja() :zegar_(0.0) {}

Symulacja::~Symulacja() {}

void Symulacja::run() 
{
  zegar_ = 0.0;
  siec_ = new Siec(this);
  //Pakiet* obecny_ = nullptr;
  for (int i = 0; i < siec_->LiczbaNad(); i++)
    (new Pakiet(i, this, siec_->getKanal(), siec_->getNad(i)))->aktywacja(siec_->getNad(i)->losujCGP());
  while (zegar_ < 20000.0) //roboczo todo
  {
    /*obecny_ = PobierzPierwszyElement()->PobierzPakiet();
    zegar_ = PobierzPierwszyElement()->PobierzCzasZd();
    this->UsunZKalendarza();*/
    Pakiet* obecny_ = kalendarz_.top()->pakiet_;
    zegar_ = kalendarz_.top()->czas_zdarzenia_;
    kalendarz_.pop();
    obecny_->UstawKolor("07");
    cout << "Pobrano z kalendarza zdarzenie o czasie: " << zegar_ << " ms" << endl;
    obecny_->execute();
    if (obecny_->CzySkonczony()) delete obecny_;
  }
}

void Symulacja::DodajDoKalendarza(Zdarzenie* zd) { kalendarz_.push(zd); }

void Symulacja::UsunZKalendarza() { kalendarz_.pop(); }

Zdarzenie* Symulacja::PobierzPierwszyElement() { return kalendarz_.top(); }
