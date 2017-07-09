#include "pakiet.h"

Pakiet::Pakiet(int idx) 
{
  id_tx_ = idx;
}
int Pakiet::getId() 
{
  return id_tx_;
}
Pakiet::~Pakiet() {}
