#include "symulacja.h"
#include "siec.h"
#include "nadajnik.h"
#include "kanal.h"
#include <cstdlib>
#include <ctime>


Siec::Siec(Symulacja* sym) 
{
  srand(time(NULL));
  sym_ = sym;
  kanal_ = new Kanal();
  for (int i = 1; i <= 1; i++) //todo
  {
    nadajniki_.push_back(new Nadajnik(i, this, kanal_));
  }
}
Siec::~Siec() {}
