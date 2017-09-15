#include "logi.h"

void Logi::WypiszLogi(int faza, long id, double zegar, int nr) 
{
    switch (faza) 
    {
    case 1: {
      if (nr == 1) {
        //UstawKolor("06");
        cout << "\nFAZA " << faza << ":\tGeneracja pakietu" << endl;
      }
      if (nr == 2) {
        //UstawKolor("0E");
        cout << "Pakiet id " << id << "\tpierwszy w buforze, sprawdza stan kanalu" << endl;
      }
    }
      break;

    case 2: {
      if (nr == 1) {
        //UstawKolor("06");
        cout << "\nFAZA " << faza << ":\tSprawdzenie kanalu" << endl;
      }
      if (nr == 2) {
        //UstawKolor("0A");
        cout << "Pakiet id " << id << ":\tKanal wolny, losuj prawdopodobienstwo" << endl;
      }
      if (nr == 3) {
        //UstawKolor("04");
        cout << "Pakiet id " << id << ":\tKanal zajety, odpytywanie co 0.5 ms" << endl;
      }
    }
      break;

    case 3: {
      if (nr == 1) {
        //UstawKolor("06");
        cout << "\nFAZA " << faza << ":\tLosowanie prawdopodobienstwa transmisji" << endl;
      }
      if (nr == 2) {
        //UstawKolor("0D");
        cout << "Pakiet id " << id << ":\tPrawdopodobienstwo transmisji mniejsze od " << 0.2
          << ", podejmij probe transmisji" << endl;
      }
      if (nr == 3) {
        //UstawKolor("0B");
        cout << "Pakiet id " << id << ":\tPrawdopodobienstwo transmisji wieksze od " << 0.2 
          << ", czekaj do nastepnej szczeliny" << ", dodaj " << (1 - fmod(zegar, 1.0)) << " ms" << endl;
      }
    }
      break;

    case 4: {
      if (nr == 1) {
        //UstawKolor("06");
        cout << "\nFAZA " << faza << ":\tPonowne sprawdzenie kanalu" << endl;
      }
      if (nr == 2) {
        //UstawKolor("0A");
        cout << "Pakiet id " << id << ":\tKanal wolny, ponowne losowanie prawdopodobienstwa" << endl;
      }
      if (nr == 3) {
        //UstawKolor("04");
        cout << "Pakiet id " << id << ":\tKanal zajety, odczekanie 1 ms i powrot do odpytywania co 0.5 ms" << endl;
      }
    }
      break;

    case 5: {
      if (nr == 1) {
        //UstawKolor("06");
        cout << "\nFAZA " << faza << ":\tDodanie do kanalu" << endl;
      }
      if (nr == 2) {
        //UstawKolor("03");
        cout << "Pakiet id " << id << ":\tdodany do kanalu" << endl;
      }
      if (nr == 3) {
        //UstawKolor("03");
        cout << "Pakiet id " << id << ":\to czasie " << zegar << " ms czeka do najblizszej szczeliny" << endl;
      }
    }
      break;

    case 6: {
      if (nr == 1) {
        //UstawKolor("06");
        cout << "\nFAZA " << faza << ":\tTransmisja pakietu " << endl;
      }
      if (nr == 2) {
        //UstawKolor("05");
        cout << "Pakiet id " << id << ":\tCzas transmisji wynosi " << zegar << " ms" << endl;
      }
    }
      break;

    case 7: {
      if (nr == 1) {
        //UstawKolor("06");
        cout << "\nFAZA " << faza << ":\tRetransmisja pakietu" << endl;
      }
      if (nr == 2) {
        //UstawKolor("01");
        cout << "Pakiet id " << id << "\tjest retransmitowany";
      }
      if (nr == 3) {
        //UstawKolor("0C");
        cout << "Pakiet id " << id << ":\tPrzekroczono liczbê dopuszczalnych retransmisji, pakiet stracony" << endl;
      }
    }
      break;

    case 8: {
      if (nr == 1) {
        //UstawKolor("06");
        cout << "\nFAZA " << faza << ":\tSprawdzenie kolizji" << endl;
      }
      if (nr == 2) {
        //UstawKolor("0F");
        cout << "Pakiet id " << id << ":\tBrak kolizji, wyslanie ACK" << endl;
      }
      if (nr == 3) {
        cout << "Pakiet id " << id << ":\tWystapila kolizja, retransmisja pakietu" << endl;
      }
    }
      break;

    case 9: {
      if (nr == 1) {
        //UstawKolor("06");
        cout << "\nFAZA " << faza << ":  Odebranie pakietu i zakonczenie transmisji" << endl;
      }
      if (nr == 2) {
        cout << "Pakiet id " << id << ":\tZostal odebrany; " << endl;
      }
    }
      break;
    }
}

/*void Logi::UstawKolor(string numer)
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
}*/
