#include "pakiet.h"
#include "symulacja.h"
#include "kanal.h"
#include "nadajnik.h"
#include "zdarzenie.h"
#include <iostream>

using std::cout;
using std::endl;

Pakiet::Pakiet(int idx, Nadajnik* tx, Kanal* kanal) :faza_(0), skonczony_(false), id_tx_(idx) 
{
  moje_zd_ = new Zdarzenie(this);
  nad_ = tx;
  kanal_ = kanal;
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
    {
      cout << "FAZA 1: Generacja pakietu" << endl;
      nad_->NowyPakiet(id_tx_);
      this->aktywacja(nad_->losujCGP());
      if (nad_->CzyPierwszy() == this) 
      {
        cout << "pakiet pierwszy w buforze, sprawdza stan kana³u" << endl;
        faza_ = 2;
      }
      aktywny_ = false;
    }
      break;
    //============================================
    // faza 2: sprawdzenie zajêtoœci kana³u
    //============================================
    case 2: 
    {
      cout << "FAZA 2: Sprawdzenie kana³u" << endl;
      if (kanal_->StanLacza() == false) 
      {
        cout << "kana³ zajêty, czekaj 0.5 ms" << endl;
        this->aktywacja(0.5);
        aktywny_ = false;
      }
      else 
      {
        cout << "kana³ wolny, podejmij próbê transmisji" << endl;
        faza_ = 3;
      }
    }
      break;
    //============================================
    // faza 3: Próba transmisji
    //         losowanie prawdopodobieñstwa
    //============================================ 
    case 3: //todo
    {
      cout << "FAZA 3: losowanie prawdopodobieñstwa transmisji" << endl;
      double p = this->losujPT();
      if (p <= 0.2) 
      {
        if (fmod(sym_->PobierzStanZegara(), 1.0) == 0) 
        {
          if (kanal_->CzyKolizja() == false) 
          {
            kanal_->DodajDoKanalu(this);
            faza_ = 6;
          }
        }
        else 
        {
          this->aktywacja(1 - fmod(sym_->PobierzStanZegara(), 1.0));
          aktywny_ = false;
        }
      }
      else 
      {
        faza_ = 5;
      }
    }
      break;//losowanie prawdopodobieñstwa
      //jeœli x<=PT to czekaj do szczeliny i sprawdŸ czy kolizja
    //============================================
    // faza 4:
    //============================================
    case 4: 
    {
    }
      break;
    //============================================
    // faza 5:
    //============================================
    case 5: 
    {
    }
      break;
    //============================================
    // faza 6:
    //============================================
    case 6: 
    {
    }
      break;
      //============================================
      // faza 7:
      //============================================
    case 7: 
    {
    }
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