#include "symulacja.h"
#include "siec.h"
#include "nadajnik.h"
#include "pakiet.h"

bool comparer::operator()(const Zdarzenie* zd1, const Zdarzenie* zd2) const
{
  if (zd1->czas_zdarzenia_ != zd2->czas_zdarzenia_)
  {
    return (zd1->czas_zdarzenia_ > zd2->czas_zdarzenia_);
  }
  return zd1->priorytet_ > zd2->priorytet_;
}

Symulacja::Symulacja(double lam, int faza, double czas, int nr, bool logi, Logi* ptr_logi, Ziarno ziarno, Statystyka* stat) :zegar_(0.0), nr_odbioru_(0)
{
  Pakiet::licznik_ = 0;
  lambda_ = lam;
  faza_poczatkowa_ = faza;
  czas_symulacji_ = czas;
  nr_symulacji_ = nr;
  log = logi;
  siec_ = new Siec(this, ziarno, stat);
  ptr_logi_ = ptr_logi;
  //opoznienie = "opoznienie" + to_string(nr) + ".txt"; //do wyznaczenia fazy pocz¹tkowej
  //plik.open(opoznienie.c_str(), ios::out | ios::app);
  //plik.open(opoznienie.c_str(), ios::out | ios::trunc);
}

Symulacja::~Symulacja()
{
  delete siec_;
  //plik.close(); //do wyznaczenia fazy pocz¹tkowej
}

void Symulacja::run(char tryb_symulacji, int nr_symulacji)
{
  cout << "\nNUMER SYMULACJI: " << nr_symulacji << endl;
  Pakiet* obecny_ = nullptr;
  while (zegar_ < czas_symulacji_)
  {
    obecny_ = kalendarz_.top()->pakiet_;
    zegar_ = kalendarz_.top()->czas_zdarzenia_;
    UsunZKalendarza();

    if (log == true) {
      UstawKolor("07");
      cout << "\nPakiet id " << obecny_->id_ << ": Pobrano z kalendarza zdarzenie o czasie: " << zegar_ << " ms";
    }

    obecny_->execute(log);
    if ((obecny_->skonczony_) == true)
    {
      if (log == true) cout << "Pakiet id " << obecny_->id_ << ":\tusuniety z systemu" << endl;
      siec_->StatystykiPakietu(obecny_);
      delete obecny_;
    }
    if (tryb_symulacji == 'K' || tryb_symulacji == 'k') getchar();
  }
  //if (plik.good() == true) //do wyznaczenia fazy pocz¹tkowej
  //{
  //  for (int i = 0; i < 100; i++)
  //    plik << tab[i] << " ";
  //}
  //else cout << "Nie uzyskano dostepu do pliku " << endl;

  siec_->Statystyki();
  siec_->CzyszczenieStatystyk();
}

void Symulacja::DodajDoKalendarza(Zdarzenie* zd) { kalendarz_.push(zd); }

void Symulacja::UsunZKalendarza()
{
  assert(!kalendarz_.empty());
  if (kalendarz_.empty() == false)
    kalendarz_.pop();
}

void Symulacja::UstawKolor(string numer)
{
  // Wybierz kolor wed³ug poni¿szego kodu:
  // Pierwszy znak odpowiada za kolor t³a pod tekstem, drugi za kolor tekstu
  //
  // Kolory podstawowe
  //
  // 0 - czarny
  // 1 - niebieski
  // 2 - zielony
  // 3 - aqua
  // 4 - czerwony
  // 5 - fioletowy
  // 6 - ¿ó³ty
  // 7 - bia³y
  // 8 - szary
  // 9 - niebieski jaskrawy
  // A - zielony jaskrawy
  // B - aqua jaskrawy
  // C - czerwony jaskrawy
  // D - fioletowy jaskrawy
  // E - ¿ó³ty jaskrawy
  // F - bia³y jaskrawy

  int kolor = 0;
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  switch (numer[0])
  {
  case '0':
    kolor += 0x00;
    break;
  case '1':
    kolor += 0x10;
    break;
  case '2':
    kolor += 0x20;
    break;
  case '3':
    kolor += 0x30;
    break;
  case '4':
    kolor += 0x40;
    break;
  case '5':
    kolor += 0x50;
    break;
  case '6':
    kolor += 0x60;
    break;
  case '7':
    kolor += 0x70;
    break;
  case '8':
    kolor += 0x80;
    break;
  case '9':
    kolor += 0x90;
    break;
  case 'A':
    kolor += 0xA0;
    break;
  case 'B':
    kolor += 0xB0;
    break;
  case 'C':
    kolor += 0xC0;
    break;
  case 'D':
    kolor += 0xD0;
    break;
  case 'E':
    kolor += 0xE0;
    break;
  case'F':
    kolor += 0xF0;
    break;
  }
  switch (numer[1])
  {
  case '0':
    kolor += 0x0;
    break;
  case '1':
    kolor += 0x1;
    break;
  case '2':
    kolor += 0x2;
    break;
  case '3':
    kolor += 0x3;
    break;
  case '4':
    kolor += 0x4;
    break;
  case '5':
    kolor += 0x5;
    break;
  case '6':
    kolor += 0x6;
    break;
  case '7':
    kolor += 0x7;
    break;
  case '8':
    kolor += 0x8;
    break;
  case '9':
    kolor += 0x9;
    break;
  case 'A':
    kolor += 0xA;
    break;
  case 'B':
    kolor += 0xB;
    break;
  case 'C':
    kolor += 0xC;
    break;
  case 'D':
    kolor += 0xD;
    break;
  case 'E':
    kolor += 0xE;
    break;
  case'F':
    kolor += 0xF;
    break;
  }

  SetConsoleTextAttribute(hOut, kolor);
}
