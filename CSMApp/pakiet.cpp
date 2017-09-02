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

Pakiet::Pakiet(int idx, Symulacja* sym, Siec* siec,Kanal* kanal, Nadajnik* nad): id_tx_(idx), faza_(1), skonczony_(false), kolizja_(false), ack_(false), nr_ret_(0)
{
  sym_ = sym;
  siec_ = siec;
  kanal_ = kanal;
  nad_ = nad;
  moje_zdarzenie_ = new Zdarzenie(this);

  czas_narodzin_ = sym_->zegar_;
  //if (czas_narodzin_ >= sym_->faza_poczatkowa_) //todo
    nad_->licznik_pakietow_++;
  czas_nadania_ = 0;
  czas_odebrania_ = 0;
  opoznienie_pakietu_ = 0;
}
Pakiet::~Pakiet() {}

void Pakiet::aktywacja(double czas)
{
  //double czas_zd = sym_->zegar_ + czas;
  moje_zdarzenie_->czas_zdarzenia_ = sym_->zegar_ + czas;
  //moje_zdarzenie_->priorytet_ = 0;
  sym_->DodajDoKalendarza(moje_zdarzenie_);
  if (sym_->logi == true) 
  {
    sym_->UstawKolor("09");
    cout << "Pakiet id " << id_tx_ << ": Dodano do kalendarza zdarzenie o czasie: "
      << moje_zdarzenie_->czas_zdarzenia_ << " ms" << endl;
  }
}

//void Pakiet::aktywacja(double czas, int priorytet) 
//{
//  //double czas_zd = sym_->zegar_ + czas;
//  moje_zdarzenie_->czas_zdarzenia_ = sym_->zegar_ + czas;
//  moje_zdarzenie_->priorytet_ = priorytet;
//  sym_->DodajDoKalendarza(moje_zdarzenie_);
//  sym_->UstawKolor("09");
//  cout << "Dodano do kalendarza zdarzenie o czasie: " << moje_zdarzenie_->czas_zdarzenia_ <<
//  " ms i priorytecie: " << moje_zdarzenie_->priorytet_ << endl;
//}

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
      if (sym_->logi == true)
      {
        sym_->UstawKolor("06");
        cout << "\nFAZA " << faza_ << ":\tGeneracja pakietu" << endl;
      }

      (new Pakiet(id_tx_, sym_, siec_, kanal_, nad_))->aktywacja(nad_->LosCGP());
      nad_->DodajDoBufora(this);
      if (nad_->PierwszyPakiet() == this) 
      {
        if (sym_->logi == true) 
        {
          sym_->UstawKolor("0E");
          cout << "Pakiet id " << id_tx_ << "\tpierwszy w buforze, sprawdza stan kanalu" << endl;
        }

        faza_ = 2;
      }
      else aktywny_ = false;
    }
      break;

    //============================================
    // faza 2: sprawdzenie zajêtoœci kana³u
    //============================================
    case 2:
    {
      if (sym_->logi == true) 
      {
        sym_->UstawKolor("06");
        cout << "\nFAZA " << faza_ << ":\tSprawdzenie kanalu" << endl;
      }

      if (kanal_->StanLacza() == false) 
      {
        if (sym_->logi == true) 
        {
          sym_->UstawKolor("04");
          cout << "Pakiet id " << id_tx_ << ":\tKanal zajety, odpytywanie co 0.5 ms" << endl;
        }

        this->aktywacja(0.5);
        aktywny_ = false;
      }
      else
      {
        if (sym_->logi == true) 
        {
          sym_->UstawKolor("0A");
          cout << "Pakiet id " << id_tx_ << ":\tKanal wolny, losuj prawdopodobienstwo" << endl;
        }

        faza_ = 3;
      }
    }
      break;

    //============================================
    // faza 3: losowanie prawdopodobieñstwa
    //============================================ 
    case 3:
    {
      if (sym_->logi == true) 
      {
        sym_->UstawKolor("06");
        cout << "\nFAZA " << faza_ << ":\tLosowanie prawdopodobienstwa transmisji" << endl;
      }

      p = nad_->LosPT();
      if (p <= kPT)
      {
        if (sym_->logi == true) 
        {
          sym_->UstawKolor("0D");
          cout << "Pakiet id " << id_tx_ << ":\tPrawdopodobienstwo transmisji p = " << p << " mniejsze od PT = " << kPT;
          cout << ", podejmij probe transmisji" << endl;
        }

        faza_ = 5;
      }
      else 
      {
        if (sym_->logi == true) 
        {
          sym_->UstawKolor("0B");
          cout << "Pakiet id " << id_tx_ << ":\tPrawdopodobienstwo transmisji p = " << p << " wieksze od PT = " << kPT << ", czekaj do nastepnej szczeliny";
          cout << ", dodaj " << (1 - fmod(sym_->zegar_, 1.0)) << " ms" << endl;
        }

        faza_ = 4;
        this->aktywacja(1 - fmod(sym_->zegar_, 1.0));
        aktywny_ = false;
      }
    }
      break;

    //============================================
    // faza 4: ponowne sprawdzanie kana³u
    //============================================
    case 4:
    {
      if (sym_->logi == true) 
      {
        sym_->UstawKolor("06");
        cout << "\nFAZA " << faza_ << ":\tPonowne sprawdzenie kanalu" << endl;
      }

      if (kanal_->StanLacza() == true)
      {
        if (sym_->logi == true) 
        {
          sym_->UstawKolor("0A");
          cout << "Pakiet id " << id_tx_ << ":\tKanal wolny, ponowne losowanie prawdopodobienstwa" << endl;
        }

        faza_ = 3;
      }
      else 
      {
        if (sym_->logi == true) 
        {
          sym_->UstawKolor("04");
          cout << "Pakiet id " << id_tx_ << ":\tKanal zajety, odczekanie 1 ms i powrot do odpytywania co 0.5 ms" << endl;
        }

        faza_ = 2;
        this->aktywacja(1.0);
        aktywny_ = false;
      }
    }
      break;

    //============================================
    // faza 5: Próba transmisji: sprawdzenie kolizji w  kanale
    //============================================
    case 5:
    {
      if (sym_->logi == true) 
      {
        sym_->UstawKolor("06");
        cout << "\nFAZA " << faza_ << ":\tSprawdzenie kolizji" << endl;
      }

      if (fmod(sym_->zegar_, 1.0) == 0.0)
      {
        if (kanal_->CzyKolizja() == true)
        {
          //if (sym_->logi == true) 
          //{
          //  sym_->UstawKolor("0A");
          //  cout << "Pakiet id " << id_tx_ << ":\tBrak kolizji, mozna transmitowac" << endl;
          //}

          if (sym_->logi == true) 
          {
            sym_->UstawKolor("04");
            cout << "Pakiet id " << id_tx_ << ":\tWykryta zostala kolizja" << endl;
          }

          for each (Pakiet* pak in kanal_->lacze_) { pak->kolizja_ = true; }
          this->kolizja_ = true;
        }
        kanal_->DodajDoKanalu(this);
        faza_ = 6;
        this->aktywacja(0.0);
        aktywny_ = false;
      }
      else
      {
        if (sym_->logi == true) 
        {
          sym_->UstawKolor("03");
          cout << "Pakiet id " << id_tx_ << " o czasie " << sym_->zegar_ << " ms czeka do najblizszej szczeliny" << endl;
        }

        this->aktywacja(1 - fmod(sym_->zegar_, 1.0));
        aktywny_ = false;
      }
    }
      break;

    //============================================
    // faza 6: W³aœciwa transmisja pakietu
    //============================================
    case 6:
    {
      if (sym_->logi == true) 
      {
        sym_->UstawKolor("06");
        cout << "\nFAZA " << faza_ << ":\tTransmisja pakietu " << endl;
      }

      czas_nadania_ = sym_->zegar_;
      //if (czas_narodzin_ >= sym_->faza_poczatkowa_) //todo
      //{
        nad_->licznik_nadanych_++;
        czas_w_buforze_ = czas_nadania_ - czas_narodzin_;
      //}

      kanal_->KanalWolny(false);
      czas_CTP_ = nad_->LosCTP();

      if (sym_->logi == true) 
      {
        sym_->UstawKolor("05");
        cout << "Pakiet id " << id_tx_ << ":\tCzas transmisji wynosi " << czas_CTP_/*ctp*/ << " ms" << endl;
      }

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
      if (sym_->logi == true)
      {
        sym_->UstawKolor("06");
        cout << "\nFAZA " << faza_ << ":\tRetransmisja pakietu" << endl;
      }

      //if (czas_narodzin_ >= sym_->faza_poczatkowa_) //todo
        nad_->licznik_ret_++;

      nr_ret_++;
      if (nr_ret_ <= kLR)
      {
        if (sym_->logi == true) 
        {
          sym_->UstawKolor("01");
          cout << "Pakiet id " << id_tx_ << "\tjest retransmitowany, numer retransmisji: " << nr_ret_ << endl;
        }

        czas_CRP_ = nad_->LosR(nr_ret_)*czas_CTP_;
        this->kolizja_ = false;
        faza_ = 2;
        this->aktywacja(czas_CRP_);
        aktywny_ = false;
      }
      else
      {
        if (sym_->logi == true) 
        {
          sym_->UstawKolor("0C");
          cout << "Pakiet id " << id_tx_ << ":\tPrzekroczono liczbê dopuszczalnych retransmisji, pakiet stracony" << endl;
        }

        //if (czas_narodzin_ >= sym_->zegar_) //todo
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
    // faza 
    //============================================
    case 8:
    {
      if (this->kolizja_ == true)
      {
        kanal_->UsunZKanalu();
        if (kanal_->CzyKolizja() == false)
          kanal_->KanalWolny(true);
        faza_ = 7;
      }
      else
      {
        faza_ = 9;
      }
    }
      break;

    //============================================
    // faza 8: Wys³anie ACK
    //============================================
    case 9:
    {
      if (sym_->logi == true)
      {
        sym_->UstawKolor("06");
        cout << "\nFAZA " << faza_ << ":\tWyslanie ACK" << endl;
      }

      ack_ = true;
      faza_ = 10;
      this->aktywacja(1.0);
      aktywny_ = false;
    }
      break;

    //============================================
    // faza 9: Odbiór pakietu i zakoñczenie transmisji
    //============================================
    case 10:
    {
      if (sym_->logi == true)
      {
        sym_->UstawKolor("06");
        cout << "\nFAZA " << faza_ << ":  Odebranie pakietu i zakonczenie transmisji" << endl;
      }
      
      czas_odebrania_ = sym_->zegar_;
      //if (czas_narodzin_ >= sym_->faza_poczatkowa_) //todo
      //{
        nad_->licznik_odebranych_++;
        opoznienie_pakietu_ = czas_odebrania_ - czas_narodzin_;
      //}

      nad_->UsunZBufora();
      kanal_->UsunZKanalu();
      kanal_->KanalWolny(true);
      skonczony_ = true;

      if (sym_->logi == true)
        cout << "Pakiet id " << id_tx_ << ":\tZostal odebrany" << endl;

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

//int Pakiet::losujCTP() 
//{
//  czas_CTP_ = (rand() % 10) + 1;
//  return czas_CTP_;
//}
//double Pakiet::losujPT() 
//{
//  double x = (rand() % 11) / 10.0;
//  return x;
//}
//double Pakiet::losujR() 
//{
//  double koniec = pow(2.0, nr_ret_) - 1;
//  double R = fmod(rand(), koniec);
//  return R;
//}
