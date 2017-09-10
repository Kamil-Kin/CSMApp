#include "pakiet.h"
#include "logi.h"
#include "symulacja.h"
#include "siec.h"
#include "kanal.h"
#include "nadajnik.h"
#include "zdarzenie.h"
#include <iostream>
#include <cmath>
#include <cassert>

using std::cout;
using std::endl;

__int64 Pakiet::licznik_ = 0;

Pakiet::Pakiet(int idx, Symulacja* sym, Siec* siec, Kanal* kanal, Nadajnik* nad) : id_tx_(idx), faza_(1), skonczony_(false), ack_(false), nr_retransmisji_(0),
czas_transmisji_(0.0), prawdopodobienstwo(0.0), czas_retransmisji_(0.0)
{
  id_ = Pakiet::licznik_;
  Pakiet::licznik_++;

  logi_ = new Logi();
  sym_ = sym;
  siec_ = siec;
  kanal_ = kanal;
  nad_ = nad;
  moje_zdarzenie_ = new Zdarzenie(this);

  czas_narodzin_ = sym_->zegar_;
  if (sym_->nr_odbioru_ > sym_->faza_poczatkowa_)
    nad_->licznik_pakietow_++;
  czas_nadania_ = 0.0;
  czas_odebrania_ = 0.0;
  opoznienie_pakietu_ = 0.0;
}
Pakiet::~Pakiet() 
{
  delete logi_;
}

void Pakiet::aktywacja(double czas)
{
  moje_zdarzenie_->czas_zdarzenia_ = sym_->zegar_ + czas;
  moje_zdarzenie_->priorytet_ = 0;
  sym_->DodajDoKalendarza(moje_zdarzenie_);
  if (sym_->logi_ == true) 
  {
    sym_->UstawKolor("09");
    cout << "Pakiet id " << id_ << ": Dodano do kalendarza zdarzenie o czasie: "
      << moje_zdarzenie_->czas_zdarzenia_ << " ms" << endl;
  }
}

void Pakiet::aktywacja(double czas, int priorytet) 
{
  moje_zdarzenie_->czas_zdarzenia_ = sym_->zegar_ + czas;
  moje_zdarzenie_->priorytet_ = priorytet;
  sym_->DodajDoKalendarza(moje_zdarzenie_);
  if (sym_->logi_ == true) 
  {
  sym_->UstawKolor("09");
  cout << "Pakiet id " << id_ << ": Dodano do kalendarza zdarzenie o czasie: " << moje_zdarzenie_->czas_zdarzenia_ <<
    " ms i priorytecie: " << moje_zdarzenie_->priorytet_ << endl;
  }
}

void Pakiet::execute(bool logi)
{
  bool aktywny_ = true;
  while (aktywny_)
  {
    switch (faza_)
    {
    //============================================
    // faza 1: generacja pakietu, dodanie do bufora
    //         sprawdzenie czy jest pierwszy w buforze
    //============================================
    case 1:
    {
      if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 1);

      (new Pakiet(id_tx_, sym_, siec_, kanal_, nad_))->aktywacja(nad_->LosCzasGeneracji());
      nad_->DodajDoBufora(this);
      if (*nad_->PierwszyPakiet() == *this)
      {
        if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 2);
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
      if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 1);

      if (kanal_->StanLacza() == true)
      {
        if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 2);
        faza_ = 3;
      }
      else
      {
        if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 3);
        aktywacja(0.5);
        aktywny_ = false;
      }
    }
      break;

    //============================================
    // faza 3: losowanie prawdopodobieñstwa
    //============================================ 
    case 3:
    {
      if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 1);

      prawdopodobienstwo = siec_->LosPrawdopodobienstwo();
      if (prawdopodobienstwo <= kPrawdopodobienstwo) 
      {
        if (logi == true) {
          logi_->WypiszLogi(faza_, id_, sym_->zegar_, 2);
          cout << "Wylosowane prawdopodobienstwo: " << prawdopodobienstwo << endl;
        }
        faza_ = 5;
      }
      else 
      {
        if (logi == true) {
          logi_->WypiszLogi(faza_, id_, sym_->zegar_, 3);
          cout << "Wylosowane prawdopodobienstwo: " << prawdopodobienstwo << endl;
        }
        faza_ = 4;
        aktywacja(1 - fmod(sym_->zegar_, 1.0)); //!!!!!!! co to jest :D - ten kod napewno do zmiany todo
        aktywny_ = false;
      }
    }
      break;

    //============================================
    // faza 4: ponowne sprawdzanie kana³u
    //============================================
    case 4:
    {
      if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 1);

      if (kanal_->StanLacza() == true)
      {
        if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 2);
        faza_ = 3;
      }
      else 
      {
        if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 3);
        faza_ = 2;
        aktywacja(1.0);
        aktywny_ = false;
      }
    }
      break;

    //============================================
    // faza 5: Próba transmisji: dodanie do kana³u
    //============================================
    case 5:
    {
      if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 1);

      if (fmod(sym_->zegar_, 1.0) == 0.0)
      {
        if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 2);
        kanal_->DodajDoKanalu(this);
        faza_ = 6;
        aktywacja(0.0, 1);
        aktywny_ = false;
      }
      else
      {
        if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 3);
        aktywacja(1 - fmod(sym_->zegar_, 1.0));
        aktywny_ = false;
      }
    }
      break;

    //============================================
    // faza 6: W³aœciwa transmisja pakietu
    //============================================
    case 6:
    {
      if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 1);

      czas_nadania_ = sym_->zegar_;
      if (sym_->nr_odbioru_ > sym_->faza_poczatkowa_) {
        nad_->licznik_nadanych_++;
        czas_w_buforze_ = czas_nadania_ - czas_narodzin_;
      }

      czas_transmisji_ = siec_->LosCzasTransmisji();
      if (logi == true) logi_->WypiszLogi(faza_, id_, czas_transmisji_, 2);
      faza_ = 8;
      aktywacja(czas_transmisji_);
      aktywny_ = false;
    }
      break;

    //============================================
    // faza 7: Retransmisja pakietu
    //============================================
    case 7:
    {
      if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 1);

      if (sym_->nr_odbioru_ > sym_->faza_poczatkowa_)
        nad_->licznik_retransmisji_++;
      nr_retransmisji_++;
      if (nr_retransmisji_ <= kMaxLiczbaRetransmisji)
      {
        if (logi == true) {
          logi_->WypiszLogi(faza_, id_, sym_->zegar_, 2);
          cout << " numer retransmisji: " << nr_retransmisji_ << endl;
        }
        czas_retransmisji_ = siec_->LosRetransmisja(nr_retransmisji_)*czas_transmisji_;
        faza_ = 2;
        aktywacja(czas_retransmisji_);
        aktywny_ = false;
      }
      else
      {
        if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 3);
        if (sym_->nr_odbioru_ > sym_->zegar_)
          nad_->licznik_straconych_++;
        nad_->UsunZBufora(this);
        skonczony_ = true;
        if (nad_->CzyBuforPusty() == false)
          nad_->PierwszyPakiet()->aktywacja(0.0);
        aktywny_ = false;
      }
    }
      break;

    //============================================
    // faza 8: Sprawdzenie, czy nast¹pi³a kolizja
    //============================================
    case 8:
    {
      if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 1);

      if (ack_ == true)
      {
        if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 2);
        faza_ = 9;
        aktywacja(kCzasPotwierdzenia);
        aktywny_ = false;
      }
      else
      {
        if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 3);
        kanal_->UsunZKanalu(this);
        faza_ = 7;
      }
    }
      break;

    //============================================
    // faza 9: Odbiór pakietu i zakoñczenie transmisji
    //============================================
    case 9:
    {
      if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 1);
      sym_->nr_odbioru_++;
      czas_odebrania_ = sym_->zegar_;
      if (sym_->nr_odbioru_ > sym_->faza_poczatkowa_) {
        nad_->licznik_odebranych_++;
        opoznienie_pakietu_ = czas_odebrania_ - czas_narodzin_;
      }

      nad_->UsunZBufora(this);
      kanal_->UsunZKanalu(this);
      skonczony_ = true;

      if (logi == true) logi_->WypiszLogi(faza_, id_, sym_->zegar_, 2);

      if (nad_->CzyBuforPusty() == false)
        nad_->PierwszyPakiet()->aktywacja(0.0);
      aktywny_ = false;
    }
      break;

    default:
      assert(true);
      break;
    }
  }
} 

bool operator==(const Pakiet & lhs, const Pakiet & rhs)
{
  return lhs.id_ == rhs.id_;
}
