#include "symulacja.h"
#include "siec.h"
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
  siec_ = new Siec(this);
  //main loop todo
  Pakiet* obecny_ = nullptr;

  while (zegar_ < 20000.0) //roboczo todo
  {
    zegar_ = 0.0;
    /*obecny_ = PobierzPierwszyElement()->PobierzPakiet();
    zegar_ = PobierzPierwszyElement()->PobierzCzasZd();
    this->UsunZKalendarza();*/
    obecny_ = kalendarz_.top()->pakiet_;
    zegar_ = kalendarz_.top()->PobierzCzasZd();
    kalendarz_.pop();
    obecny_->execute();
    if (obecny_->CzySkonczony()) delete obecny_;
  }
}

void Symulacja::DodajDoKalendarza(Zdarzenie* zd) { kalendarz_.push(zd); }

void Symulacja::UsunZKalendarza() { kalendarz_.pop(); }

Zdarzenie* Symulacja::PobierzPierwszyElement() { return kalendarz_.top(); }