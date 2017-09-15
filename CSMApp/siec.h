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

  //Losowanie parametr�w transmisji: czas transmisji, prawdopodobie�stwo i parametr R do retransmisji
  double LosCzasTransmisji();
  double LosPrawdopodobienstwo();
  double LosRetransmisja(int l_ret);

  //Obs�uga statystyk
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
  fstream plik2;  //do �redniej stopy b��d�w i wyznaczenia lambdy
  fstream plik3;  //do max stopy b��d�w
  fstream plik4;  //do przep�ywno�ci
};

#endif // !CSMA_PP_SIEC_H
