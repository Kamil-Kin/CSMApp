#include "pakiet.h"
#include "symulacja.h"
#include "nadajnik.h"
#include "zdarzenie.h"
#include <iostream>

using std::cout;
using std::endl;

Pakiet::Pakiet(int idx, Nadajnik* tx) :faza_(0), skonczony_(false), id_tx_(idx) 
{
  moje_zd_ = new Zdarzenie(this);
  nad_ = tx;
}
Pakiet::~Pakiet() {}

void Pakiet::aktywacja(double czas)
{
  moje_zd_->ustaw_czas_zd(/*zegar+*/czas);
  sym_->DodajDoKalendarza(moje_zd_);
  cout << "Dodano do kalendarza zdarzenie o czasie: " << moje_zd_->pobierz_czas_zd() << endl;
}

void Pakiet::execute()
{
  bool aktywny_ = true;
  while (aktywny_)
  {
    switch (faza_)
    {
    //============================================
    // faza 1: generacja pakietu, 
    //         sprawdzenie czy jest pierwszy w buforze
    //============================================
    case 1:
      cout << "FAZA 1: Generacja pakietu" << endl;
      nad_->NowyPakiet(id_tx_);
      this->aktywacja(nad_->losujCGP());
      if (nad_->CzyPierwszy() == this) faza_ = 2;
      aktywny_ = false;
      break;
    //============================================
    // faza 2:
    //============================================
    case 2:
      aktywny_ = false;
      break;//sprawdzenie zajêtoœci kana³u
      //jeœli wolny to faza 3
      //jesli zajêty to czekaj 0.5 ms
    //============================================
    // faza 3:
    //============================================ 
    case 3:
      break;//losowanie prawdopodobieñstwa
      //jeœli x<=PT to czekaj do szczeliny i sprawdŸ czy kolizja
    //============================================
    // faza 4:
    //============================================
    case 4:
      break;//TO DO...
    //============================================
    // faza 5:
    //============================================
    case 5:
      break;
    //============================================
    // faza 6:
    //============================================
    case 6:
      break;
      //============================================
      // faza 7:
      //============================================
    case 7:
      break;
    }
  }
}

int Pakiet::losujCTP() 
{
  int ctp = (rand() % 10) + 1;
  return ctp;
}
double Pakiet::losujPT() 
{
  double x = (rand() % 11) / 10.0;
  return x;
}