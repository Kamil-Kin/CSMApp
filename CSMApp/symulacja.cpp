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

Symulacja::Symulacja() :zegar_(0.0)
{
  //kalendarz_ = new priority_queue<Zdarzenie*, vector<Zdarzenie*>, decltype(comparer)>;
}
Symulacja::~Symulacja() {}

void Symulacja::run() 
{
  siec_ = new Siec(this);
  //main loop todo
  Pakiet* obecny_ = nullptr;

  while (StanZegara() < 2000.0) //roboczo todo
  {
    obecny_ = PobierzPierwszyElement()->PobierzPakiet();
    zegar_ = PobierzPierwszyElement()->PobierzCzasZd();
    UsunZKalendarza();
    obecny_->execute();
    if (obecny_->CzySkonczony()) delete obecny_;
  }
}

void Symulacja::DodajDoKalendarza(Zdarzenie* zd) 
{
  kalendarz_.push(zd);
  cout << "Dodano do kalendarza zdarzenie o czasie " << zd_->PobierzCzasZd() << endl;
}

void Symulacja::UsunZKalendarza()
{
  kalendarz_.pop();
  cout << "Usuni�to z kalendarza zdarzenie o czasie " << zd_->PobierzCzasZd() << endl;
}