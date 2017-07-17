#include "siec.h"
#include "nadajnik.h"
#include "pakiet.h"
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

Nadajnik::Nadajnik(int idx) :id_(idx) {}
Nadajnik::~Nadajnik() {}

void Nadajnik::NowyPakiet(int idx) 
{
  pak_ = new Pakiet(idx, this,siec_->getChannel());
}

double Nadajnik::losujCGP() 
{
  double cgp = fmod(rand(), 10.0);
  cout << "Moment wygenerowania pakietu:" << cgp << endl;
  return cgp;
}

void Nadajnik::DodajDoBufora(Pakiet* pak) 
{
  bufor_.push_back(pak);
  cout << "Dodano pakiet do bufora nadajnika nr " << id_ << endl;
}

void Nadajnik::UsunZBufora() 
{
  bufor_.pop_back();
  cout << "Usuniêto pakiet z bufora nadajnika nr " << id_ << endl;
}

Pakiet* Nadajnik::CzyPierwszy() 
{
  return bufor_.front();
}