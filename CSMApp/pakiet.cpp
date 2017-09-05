#include "pakiet.h"
#include "logi.h"
#include "symulacja.h"
#include "siec.h"
#include "kanal.h"
#include "nadajnik.h"
#include "zdarzenie.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

__int64 Pakiet::licznik_ = 0;

Pakiet::Pakiet(int idx, Symulacja* sym, Siec* siec, Kanal* kanal, Nadajnik* nad): id_tx_(idx), faza_(1), skonczony_(false), kolizja_(false), ack_(false), nr_retransmisji_(0)
{
  id_ = Pakiet::licznik_;
  Pakiet::licznik_++;
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
  moje_zdarzenie_->czas_zdarzenia_ = sym_->zegar_ + czas;
  moje_zdarzenie_->priorytet_ = 0;
  sym_->DodajDoKalendarza(moje_zdarzenie_);
  if (sym_->logi_ == true) 
  {
    sym_->UstawKolor("09");
    cout << "Pakiet id " << id_tx_ << ": Dodano do kalendarza zdarzenie o czasie: "
      << moje_zdarzenie_->czas_zdarzenia_ << " ms" << endl;
  }
}

void Pakiet::aktywacja(double czas, int priorytet) 
{
  moje_zdarzenie_->czas_zdarzenia_ = sym_->zegar_ + czas;
  moje_zdarzenie_->priorytet_ = priorytet;
  sym_->DodajDoKalendarza(moje_zdarzenie_);
  sym_->UstawKolor("09");
  cout << "Dodano do kalendarza zdarzenie o czasie: " << moje_zdarzenie_->czas_zdarzenia_ <<
  " ms i priorytecie: " << moje_zdarzenie_->priorytet_ << endl;
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
      if (logi == true)
      { // takie rzeczy jak logi powinny byc wyniesione poza ta metode
        sym_->UstawKolor("06");
        cout << "\nFAZA " << faza_ << ":\tGeneracja pakietu" << endl;
      }

      (new Pakiet(id_tx_, sym_, siec_, kanal_, nad_))->aktywacja(nad_->LosCzasGeneracji());
      nad_->DodajDoBufora(this);
      if (*nad_->PierwszyPakiet() == *this)  // teraz porownujemy id a nie wskazniki - to zawsze robi problem 
      {
        if (logi == true) 
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
      if (logi == true) 
      {
        sym_->UstawKolor("06");
        cout << "\nFAZA " << faza_ << ":\tSprawdzenie kanalu" << endl;
      }

      if (kanal_->StanLacza() == false)  // niepotrzebnie odwrocona logika ... 
      {
        if (logi == true) 
        {
          sym_->UstawKolor("04");
          cout << "Pakiet id " << id_tx_ << ":\tKanal zajety, odpytywanie co 0.5 ms" << endl;
        }

        aktywacja(0.5);
        aktywny_ = false;
      }
      else
      {
        if (logi == true) 
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
      if (logi == true) 
      {
        sym_->UstawKolor("06");
        cout << "\nFAZA " << faza_ << ":\tLosowanie prawdopodobienstwa transmisji" << endl;
      }

      p = siec_->LosPrawdopodobienstwo(); // Nieczytelne :P Ogolnie ja nie uzywalbym skrotow nigdzie -> network_->getTransmittionProbability()
      if (p <= kPrawdopodobienstwo) 
      {
        if (logi == true) 
        {
          sym_->UstawKolor("0D");
          cout << "Pakiet id " << id_tx_ << ":\tPrawdopodobienstwo transmisji p = " << p << " mniejsze od PT = " << kPrawdopodobienstwo
            << ", podejmij probe transmisji" << endl;
        }

        faza_ = 5;
      }
      else 
      {
        if (logi == true) 
        {
          sym_->UstawKolor("0B");
          cout << "Pakiet id " << id_tx_ << ":\tPrawdopodobienstwo transmisji p = " << p << " wieksze od PT = " << kPrawdopodobienstwo << ", czekaj do nastepnej szczeliny"
            << ", dodaj " << (1 - fmod(sym_->zegar_, 1.0)) << " ms" << endl;
        }

        faza_ = 4;
        aktywacja(1 - fmod(sym_->zegar_, 1.0)); //!!!!!!! co to jest :D - ten kod napewno do zmiany 
        aktywny_ = false;
      }
    }
      break;

    //============================================
    // faza 4: ponowne sprawdzanie kana³u
    //============================================
    case 4:
    {
      if (logi == true) 
      {
        sym_->UstawKolor("06");
        cout << "\nFAZA " << faza_ << ":\tPonowne sprawdzenie kanalu" << endl;
      }

      if (kanal_->StanLacza() == true)
      {
        if (logi == true) 
        {
          sym_->UstawKolor("0A");
          cout << "Pakiet id " << id_tx_ << ":\tKanal wolny, ponowne losowanie prawdopodobienstwa" << endl;
        }

        faza_ = 3;
      }
      else 
      {
        if (logi == true) 
        {
          sym_->UstawKolor("04");
          cout << "Pakiet id " << id_tx_ << ":\tKanal zajety, odczekanie 1 ms i powrot do odpytywania co 0.5 ms" << endl;
        }

        faza_ = 2;
        aktywacja(1.0);
        aktywny_ = false;
      }
    }
      break;

    //============================================
    // faza 5: Próba transmisji: sprawdzenie kolizji w  kanale
    //============================================
    case 5:
    {
      if (logi == true) 
      {
        sym_->UstawKolor("06");
        cout << "\nFAZA " << faza_ << ":\tSprawdzenie kolizji" << endl;
      }

      if (fmod(sym_->zegar_, 1.0) == 0.0)
      {
        if (kanal_->CzyKolizja() == true)
        {
          if (logi == true) 
          {
            sym_->UstawKolor("04");
            cout << "Pakiet id " << id_tx_ << ":\tWykryta zostala kolizja" << endl;
          }

          for each (Pakiet* pak in kanal_->lacze_) { pak->kolizja_ = true; } // no to jest ewidetnie zle miejsce na taka logike 
          // w tym momencie pakiet decyduje o tym ze inne pakiety sie nie powiodly - to troche nie ma sensu - wiec do wyjebania todo
          kolizja_ = true;
        }
        kanal_->DodajDoKanalu(this);
        faza_ = 6;
        aktywacja(0.0);
        aktywny_ = false;
      }
      else
      {
        if (logi == true) 
        {
          sym_->UstawKolor("03");
          cout << "Pakiet id " << id_tx_ << " o czasie " << sym_->zegar_ << " ms czeka do najblizszej szczeliny" << endl;
        }

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
      if (logi == true) 
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

      //kanal_->KanalWolny(false);
      czas_transmisji_ = siec_->LosCzasTransmisji();

      if (logi == true) 
      {
        sym_->UstawKolor("05");
        cout << "Pakiet id " << id_tx_ << ":\tCzas transmisji wynosi " << czas_transmisji_ << " ms" << endl;
      }

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
      if (logi == true)
      {
        sym_->UstawKolor("06");
        cout << "\nFAZA " << faza_ << ":\tRetransmisja pakietu" << endl;
      }

      //if (czas_narodzin_ >= sym_->faza_poczatkowa_) //todo
        nad_->licznik_retransmisji_++;

      nr_retransmisji_++;
      if (nr_retransmisji_ <= kMaxLiczbaRetransmisji) // nieczytelne max - done
      {
        if (logi == true) 
        {
          sym_->UstawKolor("01");
          cout << "Pakiet id " << id_tx_ << "\tjest retransmitowany, numer retransmisji: " << nr_retransmisji_ << endl;
        }

        czas_retransmisji_ = siec_->LosRetransmisja(nr_retransmisji_)*czas_transmisji_;
        kolizja_ = false;
        faza_ = 2;
        aktywacja(czas_retransmisji_);
        aktywny_ = false;
      }
      else
      {
        if (logi == true) 
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
    // faza sprawdzenie czy nast¹pi³a kolizja
    //============================================
    case 8:
    {
      if (kolizja_ == true)
      {
        kanal_->UsunZKanalu();
        if (kanal_->CzyKolizja() == false) // nie ma zwiazku todo
          //kanal_->KanalWolny(true); // no chyba niekoniecznie ... moze byc sytuacja gdzie sa jeszcze jakies inne pakiety w kanale 
        faza_ = 7;
      }
      else
      {
        faza_ = 9;
      }
    }
      break;

    //============================================
    // faza 9: Wys³anie ACK
    //============================================
    case 9:
    {
      if (logi == true)
      {
        sym_->UstawKolor("06");
        cout << "\nFAZA " << faza_ << ":\tWyslanie ACK" << endl;
      }

      ack_ = true; // chyba nie tutaj - zrobilbym to w nastepnej fazie - bo w czasie wysylania ACK tez moze dojsc do kolizji
      faza_ = 10;
      aktywacja(kCzasPotwierdzenia);
      aktywny_ = false;
    }
      break;

    //============================================
    // faza 10: Odbiór pakietu i zakoñczenie transmisji
    //============================================
    case 10: // troche duzo tych faz - chyba za duzo ... 
    {
      if (logi == true)
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
      //kanal_->KanalWolny(true);
      skonczony_ = true;

      if (logi == true)
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

bool operator==(const Pakiet & lhs, const Pakiet & rhs)
{
  return lhs.id_ == rhs.id_;
}
