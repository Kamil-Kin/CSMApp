#include "ziarno.h"
#include "generator_rownomierny.h"
#include "generator_wykladniczy.h"
#include "symulacja.h"
#include "siec.h"
#include "kanal.h"
#include "nadajnik.h"
#include "pakiet.h"
#include <iostream>

using std::cout;
using std::endl;

Nadajnik::Nadajnik(int idx, Ziarno ziarno, Symulacja* sym, Siec* siec, Kanal* kanal) :id_(idx)
{
  sym_ = sym;
  siec_ = siec;
  kanal_ = kanal;
  ziarno_ = ziarno;
  losCTP_ = new GenRownomierny(ziarno_.PobierzZiarno(0 + 4 * (id_ + sym_->nr_symulacji_ * siec_->LiczbaNad())));
  losPT_ = new GenRownomierny(ziarno_.PobierzZiarno(1 + 4 * (id_ + sym_->nr_symulacji_ * siec_->LiczbaNad())));
  losR_ = new GenRownomierny(ziarno_.PobierzZiarno(2 + 4 * (id_ + sym_->nr_symulacji_ * siec_->LiczbaNad())));
  losCGP_ = new GenWykladniczy(sym_->lambda_, ziarno_.PobierzZiarno(3 + 4 * (id_ + sym_->nr_symulacji_ * siec_->LiczbaNad())));
  (new Pakiet(id_, sym_, siec_, kanal_, this))->aktywacja(LosCGP());
}
Nadajnik::~Nadajnik() {}

double Nadajnik::LosCGP()
{
  //CGP_ = (rand() % 101) / 10.0;
  CGP_ = losCGP_->GeneracjaW();
  sym_->UstawKolor("02");
  cout << "Nadajnik nr " << id_ << "\tMoment wygenerowania pakietu: " << CGP_ << " ms" << endl;
  return CGP_;
}

double Nadajnik::LosCTP() { return losCTP_->GeneracjaR(1, 10); }

double Nadajnik::LosPT() { return losPT_->Generacja01(); }

double Nadajnik::LosR(int l_ret_)
{
  double koniec = pow(2.0, l_ret_) - 1;
  return losR_->GeneracjaR(0, koniec);
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
