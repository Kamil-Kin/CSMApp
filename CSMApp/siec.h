#ifndef CSMA_PP_SIEC_H
#define CSMA_PP_SIEC_H

#include <vector>
#include <iostream>
#include "statystyka.h"
#include <fstream>

class GenRownomierny;
class Symulacja;
class Nadajnik;
class Kanal;
class Pakiet;

using std::fstream;
using std::ios;
using std::vector;
using std::cout;
using std::endl;

class Siec
{
public:
  Siec(Symulacja* sym, Ziarno* ziarno, Statystyka* stat);
  ~Siec();
  int LiczbaNad() { return kLiczbaNadajnikow; }

  //Losowanie parametrów transmisji: czas transmisji, prawdopodobieñstwo i parametr R do retransmisji
  double LosCzasTransmisji();
  double LosPrawdopodobienstwo();
  double LosRetransmisja(int l_ret);

  //Obs³uga statystyk
  void CzyszczenieStatystyk();
  void Statystyki();
  void StatystykiPakietu(Pakiet* pak);

private:
  const int kLiczbaNadajnikow = 10;   //zmiana
  vector<Nadajnik*>* nadajniki_;
  Symulacja* sym_;
  Kanal* kanal_;
  Statystyka* stat_; 
  GenRownomierny* los_czas_transmisji_;
  GenRownomierny* los_prawdopodobienstwo_;
  GenRownomierny* los_retransmisja_;
  //statystyki
  double opoznienie_;
  double czas_oczekiwania_;
  fstream plik; //do zapisywania statystyk
  fstream plik2;  //do œredniej stopy b³êdów i wyznaczenia lambdy
  fstream plik3;  //do max stopy b³êdów
  fstream plik4;  //do przep³ywnoœci
};

#endif // !CSMA_PP_SIEC_H
