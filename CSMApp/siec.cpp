#include "siec.h"
#include "nadajnik.h"
#include "kanal.h"

Siec::Siec() 
{
  for (int i = 1; i <= kLiczbaNad_; i++) 
  {
    nadajniki_.push_back(new Nadajnik(i));
  }
  kanal_ = new Kanal();
}
Siec::~Siec() {}
