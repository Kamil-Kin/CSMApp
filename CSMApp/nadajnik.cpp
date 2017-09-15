#include "ziarno.h"
#include "generator_rownomierny.h"
#include "generator_wykladniczy.h"
#include "logi.h"
#include "symulacja.h"
#include "siec.h"
#include "kanal.h"
#include "nadajnik.h"
#include "pakiet.h"

Nadajnik::Nadajnik(int idx, Ziarno* ziarno, Symulacja* sym, Siec* siec, Kanal* kanal) :id_nadajnika_(idx), stopa_bledow_(0.0), licznik_generowanych_(0), licznik_nadanych_(0),
licznik_straconych_(0), licznik_odebranych_(0), licznik_retransmisji_(0)
{
  sym_ = sym;
  siec_ = siec;
  kanal_ = kanal;
  ziarno_ = ziarno;
  bufor_ = new list<Pakiet*>;
  los_czas_generacji_ = new GenWykladniczy(sym->Lambda(), ziarno->PobierzZiarno(3 + idx + sym->NrSymulacji()*(3 + siec->LiczbaNad())));
  (new Pakiet(id_nadajnika_, sym_, siec_, kanal_, this))->aktywacja(LosCzasGeneracji());
}

Nadajnik::~Nadajnik() 
{
  Pakiet* pak = nullptr;
  for (int i = 0; i < bufor_->size(); ++i) 
  {
    pak = bufor_->front();
    bufor_->pop_front();
    delete pak;
  }
  delete bufor_;
  delete los_czas_generacji_;
}

double Nadajnik::LosCzasGeneracji()
{
  czas_generacji_ = los_czas_generacji_->GeneracjaW();
  czas_generacji_ *= 10.0;
  czas_generacji_ = round(czas_generacji_);
  czas_generacji_ /= 10.0;
  if (sym_->Log() == true){
    cout << "Nadajnik nr " << id_nadajnika_ << " pakiet id " << sym_->LicznikPakietow() << "\tMoment wygenerowania pakietu: " << sym_->Zegar() + czas_generacji_ << " ms" << endl;
  }
  return czas_generacji_;
}

void Nadajnik::DodajDoBufora(Pakiet* pakiet)
{
  bufor_->push_back(pakiet);
  if (sym_->Log() == true){
    cout << "Pakiet id " << pakiet->IdPakietu() << ":\to czasie generacji " << sym_->Zegar() << " ms dodany do bufora nadajnika nr " << id_nadajnika_
      << "; ilosc pakietow w buforze: " << bufor_->size() << endl;
  }
}

void Nadajnik::UsunZBufora(Pakiet* pakiet)
{
  bufor_->remove(pakiet);
  if (sym_->Log() == true) {
    cout << "Pakiet id " << pakiet->IdPakietu() << ":\to czasie odbioru " << sym_->Zegar() << " ms usuniety z bufora nadajnika nr " << id_nadajnika_
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
