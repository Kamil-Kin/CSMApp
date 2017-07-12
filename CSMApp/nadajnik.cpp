#include "nadajnik.h"

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