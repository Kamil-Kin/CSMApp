#include "pakiet.h"
#include "symulacja.h"
#include "kanal.h"
#include "nadajnik.h"
#include "zdarzenie.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

Pakiet::Pakiet(int idx, Symulacja* sym, Kanal* kanal, Nadajnik* nad): Proces(sym), id_tx_(idx), licznik_ret_(0), ack_(false)
{
  //sym_ = sym;
  kanal_ = kanal;
  nad_ = nad;
}
Pakiet::~Pakiet() {}

void Proces::aktywacja(double czas)
{
  moje_zdarzenie_->czas_zdarzenia_ = sym_->zegar_ + czas;
  sym_->DodajDoKalendarza(moje_zdarzenie_);
  sym_->UstawKolor("09");
  cout << "Dodano do kalendarza zdarzenie o czasie: " << moje_zdarzenie_->czas_zdarzenia_ << " ms" << endl;
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
      sym_->UstawKolor("06");
      cout << "\nFAZA " << faza_ << ":\tGeneracja pakietu" << endl;
      (new Pakiet(id_tx_, sym_, kanal_, nad_))->aktywacja(nad_->losujCGP());
      nad_->DodajDoBufora(this);
      if (nad_->PierwszyPakiet() == this) 
      {
        sym_->UstawKolor("0E");
        cout << "Pakiet id " << id_tx_ << "\tpierwszy w buforze, sprawdza stan kanalu" << endl;
        faza_ = 2;
      }
      else
        aktywny_ = false;
    }
      break;

    //============================================
    // faza 2: sprawdzenie zaj�to�ci kana�u
    //============================================
    case 2: 
    {
      sym_->UstawKolor("06");
      cout << "\nFAZA " << faza_ << ":\tSprawdzenie kanalu" << endl;
      if (kanal_->StanLacza() == false) 
      {
        sym_->UstawKolor("04");
        cout << "Pakiet id " << id_tx_ << ":\tKanal zajety, odpytywanie co 0.5 ms" << endl;
        this->aktywacja(0.5);
        aktywny_ = false;
      }
      else 
      {
        sym_->UstawKolor("0A");
        cout << "Pakiet id " << id_tx_ << ":\tKanal wolny, losuj prawdopodobienstwo" << endl;
        faza_ = 3;
      }
    }
      break;

    //============================================
    // faza 3: losowanie prawdopodobie�stwa
    //============================================ 
    case 3: 
    {
      sym_->UstawKolor("06");
      cout << "\nFAZA " << faza_ << ":\tlosowanie prawdopodobienstwa transmisji" << endl;
      double p = this->losujPT();
      if (p <= kPT) 
      {
        sym_->UstawKolor("0D");
        cout << "Pakiet id " << id_tx_ << ":\tPrawdopodobienstwo transmisji p = " << p << " mniejsze od PT = " << kPT;
        cout << ", podejmij probe transmisji" << endl;
        faza_ = 5;
      }
      else 
      {
        sym_->UstawKolor("0B");
        cout << "Pakiet id " << id_tx_ << ":\tPrawdopodobienstwo transmisji p = " << p << " wieksze od PT = " << kPT << ", czekaj do nastepnej szczeliny";
        cout << ", dodaj " << (1 - fmod(sym_->zegar_, 1.0)) << " ms" << endl;
        this->aktywacja(1 - fmod(sym_->zegar_, 1.0));
        faza_ = 4;
      }
    }
      break;

    //============================================
    // faza 4: ponowne sprawdzanie kana�u
    //         z odpytywaniem co 1ms
    //============================================
    case 4: 
    {
      sym_->UstawKolor("06");
      cout << "\nFAZA " << faza_ << ":\tPonowne sprawdzenie kanalu" << endl;
      if (kanal_->StanLacza() == true) 
      {
        sym_->UstawKolor("0A");
        cout << "Pakiet id " << id_tx_ << ":\tKanal wolny, ponowne losowanie prawdopodobienstwa" << endl;
        faza_ = 3;
      }
      else 
      {
        sym_->UstawKolor("04");
        cout << "Pakiet id " << id_tx_ << ":\tKanal zajety, odpytywanie co 1.0 ms" << endl;
        this->aktywacja(1.0);
        aktywny_ = false;
      }
    }
      break;

    //============================================
    // faza 5: Pr�ba transmisji: sprawdzenie kolizji w  kanale
    //============================================
    case 5: 
    {
      sym_->UstawKolor("06");
      cout << "\nFAZA " << faza_ << ":\tSprawdzenie kolizji" << endl;
      if (fmod(sym_->zegar_, 1.0) == 0.0) 
      {
        if (kanal_->CzyKolizja() == false) 
        {
          sym_->UstawKolor("0A");
          cout << "Pakiet id " << id_tx_ << ":\tBrak kolizji, mozna transmitowac" << endl;
          kanal_->DodajDoKanalu(this);
          //kanal_->KanalWolny(false);
          faza_ = 6;
        }
        else 
        {
          sym_->UstawKolor("04");
          cout << "Pakiet id " << id_tx_ << ":\tWykryta zostala kolizja" << endl;
          faza_ = 7;
        }
      }
      else 
      {
        this->aktywacja(1 - fmod(sym_->zegar_, 1.0));
        aktywny_ = false;
      }
    }
      break;

    //============================================
    // faza 6: W�a�ciwa transmisja pakietu
    //============================================
    case 6: 
    {
      sym_->UstawKolor("06");
      cout << "\nFAZA " << faza_ << ":\tTransmisja pakietu " << endl;
      int ctp = this->losujCTP();
      sym_->UstawKolor("05");
      cout << "Pakiet id " << id_tx_ << ":\tCzas transmisji wynosi " << ctp << " ms" << endl;
      kanal_->KanalWolny(false);
      faza_ = 8;
      this->aktywacja(ctp);
      aktywny_ = false;
    }
      break;

      //============================================
      // faza 7: Retransmisja pakietu
      //============================================
    case 7: 
    {
      sym_->UstawKolor("06");
      cout << "\nFAZA " << faza_ << ":\tRetransmisja pakietu" << endl;
      licznik_ret_++;
      if (licznik_ret_ < kLR) 
      {
        sym_->UstawKolor("01");
        cout << "Pakiet id " << id_tx_ << "\tjest retransmitowany, numer retransmisji: " << licznik_ret_ << endl;
        czas_CRP_ = losujR()*czas_CTP_;
        this->aktywacja(czas_CRP_);
        faza_ = 2;
        aktywny_ = false;
      }
      else
      {
        sym_->UstawKolor("0C");
        cout << "Pakiet id " << id_tx_ << ":\tPrzekroczono liczb� dopuszczalnych retransmisji, pakiet stracony" << endl;
        nad_->UsunZBufora();
        skonczony_ = true;
      }
    }
      break;

      //============================================
      // faza 8: Odbi�r pakietu, ustawienie ACK
      //============================================
    case 8: 
    {
      sym_->UstawKolor("06");
      cout << "\nFAZA 8" << faza_ << ":\tOdbior pakietu i wyslanie ACK" << endl;
      ack_ = true;
      this->aktywacja(1.0);
      kanal_->UsunZKanalu();
      kanal_->KanalWolny(true);
      skonczony_ = true;
      aktywny_ = false;
    }
      break;
    }
  }
}

int Pakiet::losujCTP() 
{
  czas_CTP_ = (rand() % 10) + 1;
  return czas_CTP_;
}

double Pakiet::losujPT() 
{
  double x = (rand() % 11) / 10.0;
  return x;
}

double Pakiet::losujR() 
{
  double koniec = pow(2.0, licznik_ret_);
  double R = fmod(rand(), koniec);
  return R;
}

//double Pakiet::CzasZdarzenia() const { return czas_zdarzenia; }


