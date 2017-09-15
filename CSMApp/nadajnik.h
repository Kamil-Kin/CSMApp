#ifndef CSMA_PP_NADAJNIK_H
#define CSMA_PP_NADAJNIK_H

#include <list>
#include <iostream>
#include <math.h>

class Ziarno;
class GenWykladniczy;
class Symulacja;
class Siec;
class Kanal;
class Pakiet;

using std::cout;
using std::endl;
using std::list;

class Nadajnik
{
public:
  Nadajnik(int idx, Ziarno* ziarno, Symulacja* sym, Siec* siec, Kanal* kanal);
  ~Nadajnik();

  void DodajDoBufora(Pakiet* pakiet);
  void UsunZBufora(Pakiet* pakiet);
  bool CzyBuforPusty();
  Pakiet* PierwszyPakiet();

  //Losowanie czasu generacji pakietu
  double LosCzasGeneracji();

  //Pakiety wygenerowane
  void ZwiekszGenerowane() { licznik_generowanych_++; }
  int Generowane() { return licznik_generowanych_; }

  //Pakiety nadane
  void ZwiekszNadane() { licznik_nadanych_++; }
  int Nadane() { return licznik_nadanych_; }

  //Pakiety stracone
  void ZwiekszStracone() { licznik_straconych_++; }
  int Stracone() { return licznik_straconych_; }

  //Pakiety odebrane
  void ZwiekszOdebrane() { licznik_odebranych_++; }
  int Odebrane() { return licznik_odebranych_; }

  //Pakiety retransmitowane
  void ZwiekszRetransmisje() { licznik_retransmisji_++; }
  int Retransmisje() { return licznik_retransmisji_; }

  //Pakietowa stopa b³êdów
  double StopaBledow();

private:
  int id_nadajnika_;
  list<Pakiet*>* bufor_;
  int licznik_generowanych_;
  int licznik_nadanych_;
  int licznik_straconych_;
  int licznik_odebranych_;
  int licznik_retransmisji_;

  double czas_generacji_;
  double stopa_bledow_;

  Symulacja* sym_;
  Siec* siec_;
  Kanal* kanal_;
  Ziarno* ziarno_;
  GenWykladniczy* los_czas_generacji_;
};

#endif // !CSMA_PP_NADAJNIK_H
