#include "kanal.h"
#include "pakiet.h"

Kanal::Kanal() { lacze_ = new list<Pakiet*>; }

Kanal::~Kanal() { delete lacze_; }

bool Kanal::KanalWolny() { return lacze_->empty(); }

void Kanal::DodajDoKanalu(Pakiet* pakiet)
{
  lacze_->push_front(pakiet);
  if (lacze_->size() == 1)
    pakiet->UstawACK(true);
  if (lacze_->size() > 1)
    for each (Pakiet* pak in *lacze_)
      pak->UstawACK(false);
}

void Kanal::UsunZKanalu(Pakiet* pakiet) { lacze_->remove(pakiet); }
