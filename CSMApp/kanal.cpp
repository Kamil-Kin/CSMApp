#include "kanal.h"

Kanal::Kanal() /*:wolny_(true)*/ {}
Kanal::~Kanal() {}

//void Kanal::KanalWolny(bool stan_lacza) { wolny_ = stan_lacza; }

// Te dwie metody robia to samo 
bool Kanal::StanLacza() { return lacze_.empty(); }
bool Kanal::CzyKolizja() 
{
  // to powinno dzialac chyba troche inaczej - 
  // jesli dodajesz do kanalu i lacze_.size() > 1 to wszystkie pakiety w kanale powinny miec ustawiana 
  // jakas flage `kolizja` na true
  // Nie da sie tego wyciagnac poprzez metode 
  if (lacze_.size() == 0) return false;
  else return true;
}

void Kanal::DodajDoKanalu(Pakiet* pakiet) { lacze_.push_front(pakiet); }

void Kanal::UsunZKanalu() { lacze_.pop_back(); }
