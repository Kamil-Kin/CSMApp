#include "pakiet.h"
#include "siec.h"
#include "nadajnik.h"
#include "zdarzenie.h"

Pakiet::Pakiet(int idx) :faza_(0), skonczony_(false), id_tx_(idx) 
{
  moje_zd_ = new Zdarzenie(this);
}
Pakiet::~Pakiet() {}

void Pakiet::aktywacja(double czas)
{
  moje_zd_->ustaw_czas_zd(/*zegar+*/czas);
  siec_->DodajDoKalendarza(moje_zd_);
  cout << "Dodano do kalendarza zdarzenie o czasie: " << moje_zd_->pobierz_czas_zd() << endl;
}

void Pakiet::execute()
{
  bool aktywny_ = true;
  while (aktywny_)
  {
    switch (faza_)
    {
    case 1:
      cout << "FAZA 1: Generacja pakietu" << endl;
      break;
      //generacja pakietu, dodanie do bufora
      //sprawdzenie czy pierwszy w buforze, je�li tak to faza 2
    case 2:
      break;//sprawdzenie zaj�to�ci kana�u
      //je�li wolny to faza 3
      //jesli zaj�ty to czekaj 0.5 ms
    case 3:
      break;//losowanie prawdopodobie�stwa
      //je�li x<=PT to czekaj do szczeliny i sprawd� czy kolizja

    case 4:
      break;//TO DO...

    case 5:
      break;
    }
  }
}

int Pakiet::losujCTP() 
{
  //srand(time(NULL));
  int ctp = (rand() % 10) + 1;
  return ctp;
}
double Pakiet::losujPT() 
{
  double x = (rand() % 11) / 10.0;
  return x;
}