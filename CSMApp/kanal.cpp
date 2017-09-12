#include "kanal.h"
#include "pakiet.h"

Kanal::Kanal() :wolny_(true) { lacze_ = new list<Pakiet*>; }
Kanal::~Kanal() { delete lacze_; }

void Kanal::KanalWolny(bool stan_lacza) { wolny_ = stan_lacza; }

bool Kanal::StanLacza() { return lacze_->empty(); }

void Kanal::DodajDoKanalu(Pakiet* pakiet)
{
  lacze_->push_front(pakiet);
  if (lacze_->size() == 1)
    pakiet->ack_ = true;
  if (lacze_->size() > 1) 
    for each (Pakiet* pak in *lacze_)
      pak->ack_ = false;
}

void Kanal::UsunZKanalu(Pakiet* pakiet) { lacze_->remove(pakiet); }
