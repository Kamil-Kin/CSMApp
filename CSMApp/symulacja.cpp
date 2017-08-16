#include "symulacja.h"
#include "siec.h"
#include "nadajnik.h"
#include "proces.h"
#include "zdarzenie.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>
using std::cout;
using std::endl;

bool comparer::operator()(const Zdarzenie* zd1, const Zdarzenie* zd2) const
{
  return zd1->czas_zdarzenia_ > zd2->czas_zdarzenia_;
}

Symulacja::Symulacja(double lam) :zegar_(0.0), nr_symulacji_(0), liczba_symulacji_(10), czas_symulacji_(1000.0), tryb_symulacji_('c')
{
  lambda_ = lam;
}
Symulacja::~Symulacja() {}

void Symulacja::run()
{
  zegar_ = 0.0;
  siec_ = new Siec(this);
  Proces* obecny_ = nullptr;
  //for (int i = 0; i < siec_->LiczbaNad(); i++)
    //(new Pakiet(i, this, siec_->getKanal(), siec_->getNad(i)))->aktywacja(siec_->getNad(i)->losujCGP());
  while (zegar_ < czas_symulacji_)
  {
    /*obecny_ = PobierzPierwszyElement()->PobierzPakiet();
    zegar_ = PobierzPierwszyElement()->PobierzCzasZd();
    this->UsunZKalendarza();*/
    obecny_ = kalendarz_.top()->proces_;
    zegar_ = kalendarz_.top()->czas_zdarzenia_;
    kalendarz_.pop();
    UstawKolor("07");
    cout << "\nPobrano z kalendarza zdarzenie o czasie: " << zegar_ << " ms" << endl;
    obecny_->execute();
    if (obecny_->skonczony_) delete obecny_;
    if (tryb_symulacji_ == 'K' || tryb_symulacji_ == 'k') getchar();
  }
}

void Symulacja::DodajDoKalendarza(Zdarzenie* zd) { kalendarz_.push(zd); }

void Symulacja::UsunZKalendarza() { kalendarz_.pop(); }

Zdarzenie* Symulacja::PobierzPierwszyElement() { return kalendarz_.top(); }

void Symulacja::UstawKolor(string numer) {

  // Wybierz kolor wed逝g poni窺zego kodu:
  // Pierwszy znak odpowiada za kolor t豉 pod tekstem, drugi za kolor tekstu
  //
  // Kolory podstawowe
  //
  // 0 - czarny
  // 1 - niebieski
  // 2 - zielony
  // 3 - aqua
  // 4 - czerwony
  // 5 - fioletowy
  // 6 - 鄴速y
  // 7 - bia造
  // 8 - szary
  // 9 - niebieski jaskrawy
  // A - zielony jaskrawy
  // B - aqua jaskrawy
  // C - czerwony jaskrawy
  // D - fioletowy jaskrawy
  // E - 鄴速y jaskrawy
  // F - bia造 jaskrawy

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
