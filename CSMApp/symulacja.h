#ifndef CSMA_PP_SYMULACJA_H
#define CSMA_PP_SYMULACJA_H

#include "zdarzenie.h"
#include <vector>
#include <queue>

class Symulacja;
class Siec;
class Kanal;
class Nadajnik;
class Pakiet;

using std::vector;
using std::priority_queue;
using std::binary_function;

//const auto comparer = [](Zdarzenie* z1, Zdarzenie* z2)->bool
//{return z1->pobierz_czas_zd() > z2->pobierz_czas_zd(); };

struct comparer : public binary_function<Zdarzenie*, Zdarzenie*, bool> 
{ bool operator()(const Zdarzenie* z1, const Zdarzenie* z2) const; };

class Symulacja 
{
public:
  Symulacja();
  ~Symulacja();

  void run();
  double PobierzStanZegara() { return zegar_; }

  void DodajDoKalendarza(Zdarzenie* zd) { kalendarz_.push(zd); }
  void UsunZKalendarza() { kalendarz_.pop(); }
  Zdarzenie* PobierzPierwszyElement() { kalendarz_.top(); }

private:
  double zegar_;

  Symulacja* sym_;
  Siec* siec_;
  Nadajnik* nad_;
  Kanal* kanal_;
  Pakiet* pak_;

  //priority_queue<Zdarzenie*, vector<Zdarzenie*>, decltype(comparer)> kalendarz_;
  priority_queue<Zdarzenie*, vector<Zdarzenie*>, comparer> kalendarz_;
};

#endif // !CSMA_PP_SYMULACJA_H
