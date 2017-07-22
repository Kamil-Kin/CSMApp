#include "symulacja.h"
#include "siec.h"
#include "nadajnik.h"
#include "kanal.h"


Siec::Siec(Symulacja* sym) 
{

  sym_ = sym;
  kanal_ = new Kanal();
  for (int i = 1; i <= kLiczbaNad_; i++) 
  {
    nadajniki_.push_back(new Nadajnik(i, this, kanal_));
  }
}
Siec::~Siec() {}
