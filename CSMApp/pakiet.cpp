#include "pakiet.h"
#include "symulacja.h"
#include "kanal.h"
#include "nadajnik.h"
#include "zdarzenie.h"
#include <iostream>
#include <cmath>
#include <windows.h>
#include <stdlib.h>

using std::cout;
using std::endl;

Pakiet::Pakiet(int idx, Symulacja* sym, Kanal* kanal, Nadajnik* nad) :faza_(1), skonczony_(false), id_tx_(idx), licznik_ret_(0), ack_(false)
{
  sym_ = sym;
  kanal_ = kanal;
  nad_ = nad;
  moje_zd_ = new Zdarzenie(this);
  aktywacja(nad_->losujCGP());
  //execute();//todo
}
Pakiet::~Pakiet() {}

void Pakiet::aktywacja(double czas)
{
  moje_zd_->czas_zdarzenia_ = sym_->zegar_ + czas;
  //moje_zd_->UstawCzasZd(sym_->StanZegara() + czas);
  sym_->DodajDoKalendarza(moje_zd_);
  UstawKolor("09");
  cout << "Dodano do kalendarza zdarzenie o czasie: " << moje_zd_->czas_zdarzenia_ << " ms" << endl;
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
      UstawKolor("06");
      cout << "\nFAZA 1: Generacja pakietu" << endl;
      (new Pakiet(id_tx_, sym_, kanal_, nad_))->aktywacja(nad_->losujCGP());
      nad_->DodajDoBufora(this);
      if (nad_->PierwszyPakiet() == this) 
      {
        UstawKolor("0E");
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
      UstawKolor("06");
      cout << "\nFAZA 2: Sprawdzenie kanalu" << endl;
      if (kanal_->StanLacza() == false) 
      {
        UstawKolor("04");
        cout << "Kanal zajety, odpytywanie co 0.5 ms" << endl;
        this->aktywacja(0.5);
        aktywny_ = false;
      }
      else 
      {
        UstawKolor("0A");
        cout << "Kanal wolny, losuj prawdopodobienstwo" << endl;
        faza_ = 3;  //próba transmisji z p-ñstwem p
      }
    }
      break;

    //============================================
    // faza 3: losowanie prawdopodobieñstwa
    //============================================ 
    case 3: 
    {
      UstawKolor("06");
      cout << "\nFAZA 3: losowanie prawdopodobienstwa transmisji" << endl;
      double p = this->losujPT();
      if (p <= kPT) 
      {
        UstawKolor("0D");
        cout << "Prawdopodobienstwo transmisji p = " << p << " mniejsze od PT = " << kPT;
        cout << ", podejmij probe transmisji" << endl;
        faza_ = 5;
      }
      else 
      {
        UstawKolor("0B");
        cout << "Prawdopodobienstwo transmisji p = " << p << " wieksze od PT = " << kPT << ", czekaj do nastepnej szczeliny";
        cout << ", dodaj " << (1 - fmod(sym_->StanZegara(), 1.0)) << " ms" << endl;
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
      UstawKolor("06");
      cout << "\nFAZA 4: Ponowne sprawdzenie kanalu" << endl;
      if (kanal_->StanLacza() == true) 
      {
        UstawKolor("0A");
        cout << "Kanal wolny, ponowne losowanie prawdopodobienstwa" << endl;
        faza_ = 3;
      }
      else 
      {
        UstawKolor("04");
        cout << "Kanal zajety, odpytywanie co 1.0 ms" << endl;
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
      UstawKolor("06");
      cout << "\nFAZA 5: Sprawdzenie kolizji" << endl;
      if (fmod(sym_->StanZegara(), 1.0) == 0.0) 
      {
        if (kanal_->CzyKolizja() == false) 
        {
          UstawKolor("0A");
          cout << "Brak kolizji, mozna transmitowac" << endl;
          kanal_->DodajDoKanalu(this);
          kanal_->KanalWolny(false);
          faza_ = 6;
        }
        else 
        {
          UstawKolor("04");
          cout << "Wykryta zostala kolizja" << endl;
          faza_ = 7;
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
      UstawKolor("06");
      cout << "\nFAZA 6: Transmisja pakietu " << endl;
      int ctp = this->losujCTP();
      UstawKolor("05");
      cout << "Czas transmisji pakietu wynosi: " << ctp << endl;
      this->aktywacja(ctp);
      faza_ = 8;
      aktywny_ = false;
    }
      break;

      //============================================
      // faza 7: Retransmisja pakietu
      //============================================
    case 7: 
    {
      UstawKolor("06");
      cout << "\nFAZA 7: Retransmisja pakietu" << endl;
      licznik_ret_++;
      if (licznik_ret_ < kLR) 
      {
        UstawKolor("01");
        cout << "Pakiet jest retransmitowany, numer retransmisji: " << licznik_ret_ << endl;
        czas_CRP_ = losujR()*czas_CTP_;
        this->aktywacja(czas_CRP_);
        faza_ = 2;
        aktywny_ = false;
      }
      else
      {
        UstawKolor("0C");
        cout << "Przekroczono liczbê dopuszczalnych retransmisji, pakiet stracony" << endl;
        nad_->UsunZBufora();
        skonczony_ = true;
      }
    }
      break;

      //============================================
      // faza 8: Odbiór pakietu, ustawienie ACK
      //============================================
    case 8: 
    {
      UstawKolor("06");
      cout << "\nFAZA 8: Odbior pakietu i wyslanie ACK" << endl;
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
  UstawKolor("03");
  cout << "Wylosowano prawdopodobienstwo transmisji p = " << x << endl;
  return x;
}
double Pakiet::losujR() 
{
  double koniec = pow(2.0, licznik_ret_);
  double R = fmod(rand(), koniec);
  return R;
}

void Pakiet::UstawKolor(string numer) {

  // Wybierz kolor wed³ug poni¿szego kodu:
  // Pierwszy znak odpowiada za kolor t³a pod tekstem, drugi za kolor tekstu
  //
  // Kolory podstawowe
  //
  // 0 - czarny
  // 1 - niebieski
  // 2 - zielony
  // 3 - aqua
  // 4 - czerwony
  // 5 - fioletowy
  // 6 - ¿ó³ty
  // 7 - bia³y
  // 8 - szary
  // 9 - niebieski jaskrawy
  // A - zielony jaskrawy
  // B - aqua jaskrawy
  // C - czerwony jaskrawy
  // D - fioletowy jaskrawy
  // E - ¿ó³ty jaskrawy
  // F - bia³y jaskrawy

  int kolor = 0;
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  switch (numer[0])
  {
  case '0':
    kolor += 0x00;
    break;
  case '1':
    kolor += 0x10;
    break;
  case '2':
    kolor += 0x20;
    break;
  case '3':
    kolor += 0x30;
    break;
  case '4':
    kolor += 0x40;
    break;
  case '5':
    kolor += 0x50;
    break;
  case '6':
    kolor += 0x60;
    break;
  case '7':
    kolor += 0x70;
    break;
  case '8':
    kolor += 0x80;
    break;
  case '9':
    kolor += 0x90;
    break;
  case 'A':
    kolor += 0xA0;
    break;
  case 'B':
    kolor += 0xB0;
    break;
  case 'C':
    kolor += 0xC0;
    break;
  case 'D':
    kolor += 0xD0;
    break;
  case 'E':
    kolor += 0xE0;
    break;
  case'F':
    kolor += 0xF0;
    break;
  }
  switch (numer[1]) 
  {
  case '0':
    kolor += 0x0;
    break;
  case '1':
    kolor += 0x1;
    break;
  case '2':
    kolor += 0x2;
    break;
  case '3':
    kolor += 0x3;
    break;
  case '4':
    kolor += 0x4;
    break;
  case '5':
    kolor += 0x5;
    break;
  case '6':
    kolor += 0x6;
    break;
  case '7':
    kolor += 0x7;
    break;
  case '8':
    kolor += 0x8;
    break;
  case '9':
    kolor += 0x9;
    break;
  case 'A':
    kolor += 0xA;
    break;
  case 'B':
    kolor += 0xB;
    break;
  case 'C':
    kolor += 0xC;
    break;
  case 'D':
    kolor += 0xD;
    break;
  case 'E':
    kolor += 0xE;
    break;
  case'F':
    kolor += 0xF;
    break;
  }

  SetConsoleTextAttribute(hOut, kolor);
}
