#include "logi.h"

void Logi::WypiszLogi(int faza, long id, double zegar, int nr) 
{
    switch (faza) 
    {
    case 1: {
      if (nr == 1) cout << "\nFAZA " << faza << ":\tGeneracja pakietu" << endl;
      if (nr == 2) cout << "Pakiet id " << id << "\tpierwszy w buforze, sprawdza stan kanalu" << endl;
    }
      break;

    case 2: {
      if (nr == 1) cout << "\nFAZA " << faza << ":\tSprawdzenie kanalu" << endl;
      if (nr == 2) cout << "Pakiet id " << id << ":\tKanal wolny, losuj prawdopodobienstwo" << endl;
      if (nr == 3) cout << "Pakiet id " << id << ":\tKanal zajety, odpytywanie co 0.5 ms" << endl;
    }
      break;

    case 3: {
      if (nr == 1) cout << "\nFAZA " << faza << ":\tLosowanie prawdopodobienstwa transmisji" << endl;
      if (nr == 2) cout << "Pakiet id " << id << ":\tPrawdopodobienstwo transmisji mniejsze od " << 0.2 << ", podejmij probe transmisji" << endl;
      if (nr == 3) cout << "Pakiet id " << id << ":\tPrawdopodobienstwo transmisji wieksze od " << 0.2 << ", czekaj do nastepnej szczeliny" 
        << ", dodaj " << (1 - fmod(zegar, 1.0)) << " ms" << endl;
    }
      break;

    case 4: {
      if (nr == 1) cout << "\nFAZA " << faza << ":\tPonowne sprawdzenie kanalu" << endl;
      if (nr == 2) cout << "Pakiet id " << id << ":\tKanal wolny, ponowne losowanie prawdopodobienstwa" << endl;
      if (nr == 3) cout << "Pakiet id " << id << ":\tKanal zajety, odczekanie 1 ms i powrot do odpytywania co 0.5 ms" << endl;
      break;
    }
    case 5: {
      if (nr == 1) cout << "\nFAZA " << faza << ":\tDodanie do kanalu" << endl;
      if (nr == 2) cout << "Pakiet id " << id << ":\tdodany do kanalu" << endl;
      if (nr == 3) cout << "Pakiet id " << id << ":\to czasie " << zegar << " ms czeka do najblizszej szczeliny" << endl;
    }
      break;

    case 6: {
      if (nr == 1) cout << "\nFAZA " << faza << ":\tTransmisja pakietu " << endl;
      if (nr == 2) cout << "Pakiet id " << id << ":\tCzas transmisji wynosi " << zegar << " ms" << endl;
    }
      break;

    case 7: {
      if (nr == 1) cout << "\nFAZA " << faza << ":\tRetransmisja pakietu" << endl;
      if (nr == 2) cout << "Pakiet id " << id << "\tjest retransmitowany" << endl;
      if (nr == 3) cout << "Pakiet id " << id << ":\tPrzekroczono liczbê dopuszczalnych retransmisji, pakiet stracony" << endl;
    }
      break;

    case 8: {
      if (nr == 1) cout << "\nFAZA " << faza << ":\tSprawdzenie kolizji" << endl;
      if (nr == 2) cout << "Pakiet id " << id << ":\tBrak kolizji, wyslanie ACK" << endl;
      if (nr == 3) cout << "Pakiet id " << id << ":\tWystapila kolizja, retransmisja pakietu" << endl;
    }
      break;

    case 9: {
      if (nr == 1) cout << "\nFAZA " << faza << ":  Odebranie pakietu i zakonczenie transmisji" << endl;
      if (nr == 2) cout << "Pakiet id " << id << ":\tZostal odebrany; " << endl;
    }
      break;
    }
}
