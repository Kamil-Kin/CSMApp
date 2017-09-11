#ifndef CSMA_PP_SYMULACJA_H
#define CSMA_PP_SYMULACJA_H

#include <vector>
#include <queue>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include "zdarzenie.h"
#include "statystyka.h"
#include "logi.h"
//#include <fstream>

class Ziarno;
class Siec;
class Zdarzenie;
class Pakiet;

using std::cout;
using std::endl;
using std::vector;
using std::priority_queue;
using std::binary_function; 
using std::string;
//using std::fstream; //do wyznaczenia fazy pocz¹tkowej
//using std::ios;
//using std::to_string;

//const auto comparer = [](Zdarzenie* z1, Zdarzenie* z2)->bool
//{ return z1->czas_zdarzenia_ > z2->czas_zdarzenia_; };
struct comparer : public binary_function<Zdarzenie*, Zdarzenie*, bool>
{
  bool operator()(const Zdarzenie* zd1, const Zdarzenie* zd2) const;
};

class Symulacja
{
public:
  Symulacja(double lam, int faza, double czas_sym, int nr_sym, bool logi, Logi* ptr_logi, Ziarno ziarno, Statystyka* stat);
  ~Symulacja();

  void run(char tryb, int nr);
  void DodajDoKalendarza(Zdarzenie* zd);
  void UsunZKalendarza();
  void UstawKolor(string numer);

  double zegar_;
  double lambda_;
  int faza_poczatkowa_;
  double czas_symulacji_;
  int nr_symulacji_;
  bool log;
  int nr_odbioru_; 
  Logi* ptr_logi_;
  //do wyznaczenia fazy pocz¹tkowej
  //fstream plik; 
  //string opoznienie; 
  //double tab[20000] = { 0.0 };
private:
  Siec* siec_;
  Zdarzenie* zd_;
  priority_queue<Zdarzenie*, vector<Zdarzenie*>, comparer> kalendarz_;
  //priority_queue<Zdarzenie*, vector<Zdarzenie*>, decltype(comparer)> kalendarz_;
};

#endif // !CSMA_PP_SYMULACJA_H
