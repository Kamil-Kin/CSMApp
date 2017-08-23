#include "pakiet.h"
#include "symulacja.h"
#include "siec.h"
#include "kanal.h"
#include "nadajnik.h"
#include "zdarzenie.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

Pakiet::Pakiet(int idx, Symulacja* sym, Siec* siec,Kanal* kanal, Nadajnik* nad): id_tx_(idx), faza_(1), skonczony_(false), ack_(false), nr_ret_(0)
{
  sym_ = sym;
  siec_ = siec;
  kanal_ = kanal;
  nad_ = nad;
  moje_zdarzenie_ = new Zdarzenie(this);

  nad_->licznik_pakietow_++;
  czas_narodzin_ = sym_->zegar_;
  czas_nadania_ = 0;
  czas_odebrania_ = 0;
  opoznienie_pakietu_ = 0;
}
Pakiet::~Pakiet() {}

void Pakiet::aktywacja(double czas)
{
  //double czas_zd = sym_->zegar_ + czas;
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
      (new Pakiet(id_tx_, sym_, siec_, kanal_, nad_))->aktywacja(nad_->LosCGP());
      nad_->DodajDoBufora(this);
      if (nad_->PierwszyPakiet() == this) 
      {
        sym_->UstawKolor("0E");
        cout << "Pakiet id " << id_tx_ << "\tpierwszy w buforze, sprawdza stan kanalu" << endl;
        faza_ = 2;
      }
      else aktywny_ = false;
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
      cout << "\nFAZA " << faza_ << ":\tLosowanie prawdopodobienstwa transmisji" << endl;
      p = losujPT();//p = nad_->LosPT();
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
        faza_ = 4;
        this->aktywacja(1 - fmod(sym_->zegar_, 1.0));
        aktywny_ = false;
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
        faza_ = 2;
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
          faza_ = 6;
          this->aktywacja(0.0);
          aktywny_ = false;
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
        sym_->UstawKolor("03");
        cout << "Pakiet id " << id_tx_ << " o czasie " << sym_->zegar_ << " ms czeka do najblizszej szczeliny" << endl;
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
      nad_->licznik_nadanych_++;
      czas_nadania_ = sym_->zegar_;
      czas_w_buforze_ = czas_nadania_ - czas_narodzin_;
      czas_CTP_ = this->losujCTP();//czas_CTP_ = nad_->LosCTP();
      sym_->UstawKolor("05");
      cout << "Pakiet id " << id_tx_ << ":\tCzas transmisji wynosi " << czas_CTP_/*ctp*/ << " ms" << endl;
      kanal_->KanalWolny(false);
      faza_ = 8;
      this->aktywacja(czas_CTP_);
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
      nad_->licznik_ret_++;
      nr_ret_++;
      if (nr_ret_ <= kLR) 
      {
        sym_->UstawKolor("01");
        cout << "Pakiet id " << id_tx_ << "\tjest retransmitowany, numer retransmisji: " << nr_ret_ << endl;
        czas_CRP_ = losujR()*czas_CTP_;//czas_CRP_ = nad_->LosR(nr_ret_)*czas_CTP_;
        this->aktywacja(czas_CRP_);
        faza_ = 2;
        aktywny_ = false;
      }
      else
      {
        sym_->UstawKolor("0C");
        cout << "Pakiet id " << id_tx_ << ":\tPrzekroczono liczb� dopuszczalnych retransmisji, pakiet stracony" << endl;
        nad_->licznik_straconych_++;
        nad_->UsunZBufora();
        skonczony_ = true;
        if (nad_->CzyBuforPusty() == false)
          nad_->PierwszyPakiet()->aktywacja(0.0);
        aktywny_ = false;
      }
    }
      break;

    //============================================
    // faza 8: Wys�anie ACK
    //============================================
    case 8: 
    {
      sym_->UstawKolor("06");
      cout << "\nFAZA " << faza_ << ":\tWyslanie ACK" << endl;
      ack_ = true;
      this->aktywacja(1.0);
      faza_ = 9;
      aktywny_ = false;
    }
      break;

    //============================================
    // faza 9: Odbi�r pakietu i zako�czenie transmisji
    //============================================
    case 9: 
    {
      sym_->UstawKolor("06");
      cout << "\nFAZA " << faza_ << ":\tOdebranie pakietu i zakonczenie transmisji" << endl;
      nad_->licznik_odebranych_++;
      czas_odebrania_ = sym_->zegar_;
      opoznienie_pakietu_ = czas_odebrania_ - czas_narodzin_;
      nad_->UsunZBufora();
      kanal_->UsunZKanalu();
      kanal_->KanalWolny(true);
      skonczony_ = true;
      cout << "Pakiet id " << id_tx_ << " zostal odebrany" << endl;
      if (nad_->CzyBuforPusty() == false) 
        nad_->PierwszyPakiet()->aktywacja(0.0);
      aktywny_ = false;
    }
      break;

    default:
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
  double koniec = pow(2.0, nr_ret_) - 1;
  double R = fmod(rand(), koniec);
  return R;
}
