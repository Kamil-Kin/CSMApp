#include "kanal.h"

Kanal::Kanal() :wolny_(true), liczba_pakietow_(0) {}
Kanal::~Kanal() {}

void Kanal::KanalWolny(bool stan_lacza) { wolny_ = stan_lacza; }

bool Kanal::StanLacza() { return wolny_; }

bool Kanal::CzyKolizja() 
{
  if (lacze_.size() == 0) return false;
  return true;
}

void Kanal::DodajDoKanalu(Pakiet* pakiet) { lacze_.push_front(pakiet); }

void Kanal::UsunZKanalu() { lacze_.pop_back(); }
