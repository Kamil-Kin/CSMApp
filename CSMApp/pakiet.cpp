#include "pakiet.h"

void Pakiet::aktywacja(double czas)
{
  moje_zd_->ustaw_czas_zd(/*zegar*/+czas);
  getTxId()->getWebId()->DodajDoKalendarza(moje_zd_);
}

void Pakiet::execute() 
{
  bool aktywny_ = true;
  while (aktywny_) 
  {
    switch (faza_) 
    {
    case 1: //generacja pakietu, dodanie do bufora
      //sprawdzenie czy pierwszy w buforze, je�li tak to faza 2
    case 2://sprawdzenie zaj�to�ci kana�u
      //je�li wolny to faza 3
      //jesli zaj�ty to czekaj 0.5 ms
    case 3://losowanie prawdopodobie�stwa
      //je�li x<=PT to czekaj do szczeliny i sprawd� czy kolizja

    case 4://TO DO...

    case 5:
    }
  }
}