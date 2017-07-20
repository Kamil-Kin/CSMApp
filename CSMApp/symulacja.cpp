#include "symulacja.h"
#include "siec.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>

bool comparer::operator()(const Zdarzenie* z1, const Zdarzenie* z2) const
{
  if (z1 != nullptr && z2 != nullptr) 
  {
    if (z1->pobierz_czas_zd() > z2->pobierz_czas_zd())
      return true;
  }
  else return false;
}

Symulacja::Symulacja() :zegar_(0.0)
{
  //kalendarz_ = new priority_queue<Zdarzenie*, vector<Zdarzenie*>, decltype(comparer)>;
}
Symulacja::~Symulacja() {}

void Symulacja::run() 
{
  srand(time(NULL));
  
  siec_ = new Siec(this);
  //main loop todo
  getchar();

}