#include "kanal.h"

Kanal::Kanal()
{
  czy_wolny_ = true;
}
void Kanal::UstawLacze(bool stan_lacza) 
{
  czy_wolny_ = stan_lacza;
}
bool Kanal::StanLacza() 
{
  return czy_wolny_;
}
Kanal::~Kanal() {}