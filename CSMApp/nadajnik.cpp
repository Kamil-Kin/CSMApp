//#include "symulacja.h"
#include "siec.h"
#include "kanal.h"
#include "nadajnik.h"
#include "pakiet.h"
#include <iostream>

using std::cout;
using std::endl;

Nadajnik::Nadajnik(int idx, Siec* siec, Kanal* kanal) :id_(idx) 
{
  siec_ = siec;
  kanal_ = kanal;
  pak_ = new Pakiet(idx, siec_->getSim(), kanal, this);
}
Nadajnik::~Nadajnik() {}

double Nadajnik::losujCGP() 
{
  double cgp = fmod(rand(), 10.0) + 1;
  pak_->UstawKolor("02");
  cout << "Moment wygenerowania pakietu: " << cgp << endl;
  return cgp;
}

void Nadajnik::DodajDoBufora(Pakiet* pak) 
{
  bufor_.push_back(pak);
  pak_->UstawKolor("0F");
  cout << "Dodano pakiet do bufora nadajnika nr " << id_ << endl;
}

void Nadajnik::UsunZBufora() 
{
  bufor_.pop_back();
  cout << "Usuniêto pakiet z bufora nadajnika nr " << id_ << endl;
}

Pakiet* Nadajnik::PierwszyPakiet() 
{
  return bufor_.front();
}