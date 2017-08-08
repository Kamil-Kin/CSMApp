#include "proces.h"
#include "zdarzenie.h"
#include "symulacja.h"
#include <iostream>

using std::cout;
using std::endl;

Proces::Proces(Symulacja* sym) :faza_(1), skonczony_(false)
{
  sym_ = sym;
  moje_zdarzenie_ = new Zdarzenie(this);
}

Proces::~Proces() {}
