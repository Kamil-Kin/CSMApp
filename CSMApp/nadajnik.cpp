#include "symulacja.h"
#include "siec.h"
#include "kanal.h"
#include "nadajnik.h"
#include "pakiet.h"
#include <iostream>

using std::cout;
using std::endl;

Nadajnik::Nadajnik(int idx, Symulacja* sym, Siec* siec, Kanal* kanal) :id_(idx)
{
  sym_ = sym;
  siec_ = siec;
  kanal_ = kanal;
  pak_ = new Pakiet(idx, siec_->getSim(), kanal_, this);
  pak_->aktywacja(losujCGP());

}
Nadajnik::~Nadajnik() {}

double Nadajnik::losujCGP()
{
  CGP_ = (rand() % 101) / 10.0;
  //double cgp = fmod(rand(), 10.0) + 1;
  sym_->UstawKolor("02");
  cout << "Nadajnik nr " << id_ << "\tMoment wygenerowania pakietu: " << CGP_ << " ms" << endl;
  return CGP_;
}

void Nadajnik::DodajDoBufora(Pakiet* pak) 
{
  bufor_.push_back(pak);
  sym_->UstawKolor("0F");
  cout << "Dodano pakiet do bufora nadajnika nr " << id_ << endl;
}

void Nadajnik::UsunZBufora() 
{
  bufor_.pop_back();
  sym_->UstawKolor("08");
  cout << "Usunieto pakiet z bufora nadajnika nr " << id_ << endl;
}

bool Nadajnik::CzyBuforPusty() { return bufor_.empty(); }
Pakiet* Nadajnik::PierwszyPakiet() { return bufor_.front(); }
