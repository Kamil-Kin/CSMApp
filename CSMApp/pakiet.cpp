#include "pakiet.h"
#include "symulacja.h"
#include "kanal.h"
#include "nadajnik.h"
#include "zdarzenie.h"
#include <iostream>

using std::cout;
using std::endl;

Pakiet::Pakiet(int idx, Symulacja* sym, Kanal* kanal, Nadajnik* nad) :faza_(1), skonczony_(false), id_tx_(idx) 
{
  sym_ = sym;
  kanal_ = kanal;
  nad_ = nad;
  moje_zd_ = new Zdarzenie(this);
  //aktywacja(nad_->losujCGP());
  execute();//todo
}
Pakiet::~Pakiet() {}

void Pakiet::aktywacja(double czas)
{
  moje_zd_->UstawCzasZd(sym_->StanZegara() + czas);
  sym_->DodajDoKalendarza(moje_zd_);
  cout << "Dodano do kalendarza zdarzenie o czasie: " << moje_zd_->PobierzCzasZd() << endl;
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
      aktywacja(nad_->losujCGP());
      nad_->DodajDoBufora(this);
      if (nad_->CzyPierwszy() == this) 
      {
        cout << "Pakiet pierwszy w buforze, sprawdza stan kanalu" << endl;
        faza_ = 2;
      }
      else
        aktywny_ = false;
    }
      break;

    //============================================
    // faza 2: sprawdzenie zajêtoœci kana³u
    //============================================
    case 2: 
    {
      cout << "FAZA 2: Sprawdzenie kanalu" << endl;
      if (kanal_->StanLacza() == false) 
      {
        cout << "Kanal zajety, czekaj 0.5 ms" << endl;
        this->aktywacja(0.5);
        aktywny_ = false;
      }
      else 
      {
        cout << "Kanal wolny, podejmij probe transmisji" << endl;
        faza_ = 3;  //próba transmisji z p-ñstwem p
      }
    }
      break;

    //============================================
    // faza 3: losowanie prawdopodobieñstwa
    //============================================ 
    case 3: 
    {
      cout << "FAZA 3: losowanie prawdopodobieñstwa transmisji" << endl;
      double p = this->losujPT();
      if (p <= kPT) 
      {
        cout << "Prawdopodobienstwo transmisji p = " << p << " mniejsze od PT = " << kPT << endl;
        cout << "Mozna podjac probe transmisji" << endl;
        faza_ = 5;
      }
      else 
      {
        cout << "Prawdopodobienstwo transmisji p = " << p << " wieksze od PT = " << kPT << endl;
        this->aktywacja(1 - fmod(sym_->StanZegara(), 1.0));
        faza_ = 4;
      }
    }
      break;

    //============================================
    // faza 4: ponowne sprawdzanie kana³u
    //         z odpytywaniem co 1ms
    //============================================
    case 4: 
    {
      cout << "FAZA 4: Ponowne sprawdzenie kanalu" << endl;
      if (kanal_->StanLacza() == true) 
      {
        cout << "Kanal wolny, ponowne losowanie prawdopodobienstwa" << endl;
        faza_ = 3;
      }
      else 
      {
        cout << "Kanal zajety, odpytywanie co 1.0 ms" << endl;
        this->aktywacja(1.0);
        aktywny_ = false;
      }
    }
      break;
    //============================================
    // faza 5: Próba transmisji: sprawdzenie zajêtoœci kana³u
    //============================================
    case 5: 
    {
      cout << "FAZA 5: " << endl;
      if (fmod(sym_->StanZegara(), 1.0) == 0.0) 
      {
        if (kanal_->CzyKolizja() == false) 
        {
          kanal_->DodajDoKanalu(this);
          faza_ = 6;
        }
        else 
        {
          cout << "Wykryta zostala kolizja" << endl;
          //todo
        }
      }
      else 
      {
        this->aktywacja(1 - fmod(sym_->StanZegara(), 1.0));
        aktywny_ = false;
      }
    }
      break;

    //============================================
    // faza 6: W³aœciwa transmisja pakietu
    //============================================
    case 6: 
    {
      cout << "FAZA 6:" << endl;
      this->aktywacja(this->losujCTP());
      aktywny_ = false;
    }
      break;

      //============================================
      // faza 7:
      //============================================
    case 7: 
    {
      cout << "FAZA 7: " << endl;
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
  cout << "Wylosowano prawdopodobienstwo transmisji p = " << x << endl;
  return x;
}