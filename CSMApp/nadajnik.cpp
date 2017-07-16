#include "siec.h"
#include "nadajnik.h"
#include "pakiet.h"

Nadajnik::Nadajnik(int idx) :id_(idx) 
{
  frame_ = new Pakiet(idx);
}
Nadajnik::~Nadajnik() {}

void Nadajnik::DodajDoBufora(Pakiet* pak) 
{
  bufor_.push_back(pak);
  std::cout << "Dodano pakiet do bufora nadajnika nr " << id_ << std::endl;
}

void Nadajnik::UsunZBufora() 
{
  bufor_.pop_back();
  std::cout << "Usuniêto pakiet z bufora nadajnika nr " << id_ << std::endl;
}

Pakiet* Nadajnik::CzyPierwszy() 
{
  return bufor_.front();
}

Siec* Nadajnik::getWebId() 
{
  return siec_;
}