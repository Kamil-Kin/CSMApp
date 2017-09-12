#include "ziarno.h"
#include "generator_rownomierny.h"
#include "generator_wykladniczy.h"
#include "logi.h"
#include "symulacja.h"
#include "siec.h"
#include "kanal.h"
#include "nadajnik.h"
#include "pakiet.h"

Nadajnik::Nadajnik(int idx, Ziarno ziarno, Symulacja* sym, Siec* siec, Kanal* kanal) :id_(idx), stopa_bledow_(0.0), licznik_pakietow_(0), licznik_nadanych_(0),
licznik_straconych_(0), licznik_odebranych_(0), licznik_retransmisji_(0)
{
  sym_ = sym;
  siec_ = siec;
  kanal_ = kanal;
  ziarno_ = ziarno;
  bufor_ = new list<Pakiet*>;
  los_czas_generacji_ = new GenWykladniczy(sym_->lambda_, ziarno_.PobierzZiarno(3 + id_ + sym_->nr_symulacji_*(3 + siec_->LiczbaNad())));
  (new Pakiet(id_, sym_, siec_, kanal_, this))->aktywacja(LosCzasGeneracji());
}

Nadajnik::~Nadajnik() 
{
  for (int i = 0; i < bufor_->size(); ++i)
    bufor_->pop_back();
  delete bufor_;
  delete los_czas_generacji_;
}

double Nadajnik::LosCzasGeneracji()
{
  czas_generacji_ = los_czas_generacji_->GeneracjaW();
  czas_generacji_ *= 10;
  czas_generacji_ = round(czas_generacji_);
  czas_generacji_ /= 10;
  if (sym_->log == true)
  {
    //sym_->UstawKolor("02");
    cout << "Nadajnik nr " << id_ << " pakiet id " << Pakiet::licznik_ << "\tMoment wygenerowania pakietu: " << sym_->zegar_ + czas_generacji_ << " ms" << endl;
  }
  return czas_generacji_;
}

void Nadajnik::DodajDoBufora(Pakiet* pakiet)
{
  bufor_->push_back(pakiet);
  if (sym_->log == true)
  {
    //sym_->UstawKolor("0F");
    cout << "Pakiet id " << pakiet->id_ << ":\to czasie generacji " << sym_->zegar_ << " ms dodany do bufora nadajnika nr " << id_
      << "; ilosc pakietow w buforze: " << bufor_->size() << endl;
  }
}

void Nadajnik::UsunZBufora(Pakiet* pakiet)
{
  bufor_->remove(pakiet);
  if (sym_->log == true) 
  {
    //sym_->UstawKolor("08");
    cout << "Pakiet id " << pakiet->id_ << ":\to czasie odbioru " << sym_->zegar_ << " ms usuniety z bufora nadajnika nr " << id_
      << "; ilosc pakietow w buforze: " << bufor_->size() << endl;
  }
}

bool Nadajnik::CzyBuforPusty() { return bufor_->empty(); }

Pakiet* Nadajnik::PierwszyPakiet() { return bufor_->front(); }

double Nadajnik::StopaBledow() 
{
  stopa_bledow_ = licznik_straconych_ / static_cast<double>(licznik_nadanych_);
  return stopa_bledow_;
}
