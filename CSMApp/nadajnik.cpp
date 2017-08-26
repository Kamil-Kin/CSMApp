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

Nadajnik::Nadajnik(int idx, Ziarno ziarno, Symulacja* sym, Siec* siec, Kanal* kanal) :id_(idx), stopa_bledow_(0.0), licznik_pakietow_(0), licznik_nadanych_(0),
licznik_straconych_(0), licznik_odebranych_(0), licznik_ret_(0)
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

Nadajnik::~Nadajnik() 
{
  //CzyszczenieStatystykNad();
}

double Nadajnik::LosCGP()
{
  CGP_ = (rand() % 101) / 10.0;
  //CGP_ = losCGP_->GeneracjaW();
  sym_->UstawKolor("02");
  cout << "Nadajnik nr " << id_ << "\tMoment wygenerowania pakietu: " << sym_->zegar_ + CGP_ << " ms" << endl;
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
  cout << "Dodano pakiet o czasie generacji " << sym_->zegar_ << " ms do bufora nadajnika nr " << id_
    << "; ilosc pakietow w buforze: " << bufor_.size() << endl;
}

void Nadajnik::UsunZBufora() 
{
  bufor_.pop_back();
  sym_->UstawKolor("08");
  cout << "Usunieto pakiet o czasie odbioru " << sym_->zegar_ << " ms z bufora nadajnika nr " << id_
    << "; ilosc pakietow w buforze: " << bufor_.size() << endl;
}

bool Nadajnik::CzyBuforPusty() { return bufor_.empty(); }

Pakiet* Nadajnik::PierwszyPakiet() { return bufor_.front(); }

double Nadajnik::StopaBledow() 
{
  stopa_bledow_ = licznik_straconych_ / static_cast<double>(licznik_pakietow_);
  return stopa_bledow_;
}

void Nadajnik::CzyszczenieStatystykNad() 
{
  stopa_bledow_ = 0.0;
  licznik_pakietow_ = 0;
  licznik_nadanych_ = 0;
  licznik_straconych_ = 0;
  licznik_odebranych_ = 0;
}
