#include "nadajnik.h"

Nadajnik::Nadajnik(int idx) 
{
  id_ = idx;
  frame_ = new Pakiet(idx);
}

Nadajnik::~Nadajnik() {}