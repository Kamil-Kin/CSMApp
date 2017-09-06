#include "kanal.h"
#include "pakiet.h"

Kanal::Kanal() :wolny_(true) {}
Kanal::~Kanal() {}

void Kanal::KanalWolny(bool stan_lacza) { wolny_ = stan_lacza; }

bool Kanal::StanLacza() { return lacze_.empty(); }

 // to powinno dzialac chyba troche inaczej - 
 // jesli dodajesz do kanalu i lacze_.size() > 1, 
  //to wszystkie pakiety w kanale powinny miec ustawiana 
 // jakas flage `kolizja` na true
 // Nie da sie tego wyciagnac poprzez metode 

void Kanal::DodajDoKanalu(Pakiet* pakiet)
{
  lacze_.push_front(pakiet);
  if (lacze_.size() > 1) 
    for each (Pakiet* pak in lacze_)
      pak->kolizja_ = true;
}

void Kanal::UsunZKanalu(Pakiet* pakiet) { lacze_.remove(pakiet); }
