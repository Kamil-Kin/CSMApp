#include "ziarno.h"
#include "generator_rownomierny.h"
#include "symulacja.h"
#include "siec.h"
#include "nadajnik.h"
#include "kanal.h"
#include <cstdlib>
#include <ctime>

Siec::Siec(Symulacja* sym, int nr_sym) 
{
  srand(time(NULL));
  ziarno_ = new Ziarno();
  sym_ = sym;
  kanal_ = new Kanal();
  for (int i = 0; i < kLiczbaNad_; i++)
  {
    losCTP_ = new GenRownomierny(ziarno_->PobierzZiarno(0 + i * 4));
    losPT_ = new GenRownomierny(ziarno_->PobierzZiarno(1 + i * 4));
    losR_ = new GenRownomierny(ziarno_->PobierzZiarno(2 + i * 4));
    nadajniki_.push_back(new Nadajnik(i, sym_, this, kanal_));
  }
}
Siec::~Siec() {}

double Siec::LosCTP() { return losCTP_->GeneracjaR(1, 10); }

double Siec::LosPT() { return losPT_->Generacja01(); }

double Siec::LosR(int l_ret_)
{
  double koniec = pow(2.0, l_ret_) - 1;
  return losR_->GeneracjaR(0, koniec);
}
