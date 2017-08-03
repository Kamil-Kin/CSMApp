#include "kanal.h"

Kanal::Kanal()
{
  czy_wolny_ = true;
}
Kanal::~Kanal() {}

void Kanal::KanalWolny(bool stan_lacza) 
{
  czy_wolny_ = stan_lacza;
}
bool Kanal::StanLacza() 
{
  return czy_wolny_;
}
bool Kanal::CzyKolizja() 
{
  if (lacze_.empty()) return false;
  return true;
}
void Kanal::DodajDoKanalu(Pakiet* pakiet)
{
  lacze_.push_back(pakiet);
}
void Kanal::UsunZKanalu() 
{
  lacze_.pop_back();
}
