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
      //sprawdzenie czy pierwszy w buforze, jeœli tak to faza 2
    case 2://sprawdzenie zajêtoœci kana³u
      //jeœli wolny to faza 3
      //jesli zajêty to czekaj 0.5 ms
    case 3://losowanie prawdopodobieñstwa
      //jeœli x<=PT to czekaj do szczeliny i sprawdŸ czy kolizja

    case 4://TO DO...

    case 5:
    }
  }
}