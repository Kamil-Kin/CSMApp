#include "nadajnik.h"
#include "pakiet.h"
#include <iostream>

using std::vector;

Nadajnik::Nadajnik(int idx) :id_(idx) 
{
  frame_ = new Pakiet(idx);
}
Nadajnik::~Nadajnik() {}

double Nadajnik::losujCGP() 
{
  return fmod(rand(), 10.0);
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