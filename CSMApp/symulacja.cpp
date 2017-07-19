#include "symulacja.h"
#include "siec.h"
#include "kanal.h"
#include "nadajnik.h"
#include "pakiet.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>

bool comparer::operator()(const Zdarzenie* z1, const Zdarzenie* z2) const
{
  if (z1 != nullptr && z2 != nullptr) 
  {
    if (z1->pobierz_czas_zd() > z2->pobierz_czas_zd())
      return true;
    if (z1->pobierz_czas_zd() < z2->pobierz_czas_zd())
      return false;
    return false; 
  }
  else return false;
}


Symulacja::Symulacja() :zegar_(0.0)
{
  siec_ = new Siec();
  //kalendarz_ = new priority_queue<Zdarzenie*, vector<Zdarzenie*>, decltype(comparer)>;
}
Symulacja::~Symulacja() {}

void Symulacja::run() 
{
  srand(time(NULL));

  (new Pakiet(4, sym_, kanal_, nad_))->execute();
  getchar();

}