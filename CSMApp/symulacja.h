#ifndef CSMA_PP_SYMULACJA_H
#define CSMA_PP_SYMULACJA_H

#include "siec.h"
#include "zdarzenie.h"
#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;

const auto comparer = [](Zdarzenie* z1, Zdarzenie* z2) {
  return z1->pobierz_czas_zd() > z2->pobierz_czas_zd(); };

class Symulacja 
{
public:
  Symulacja() :zegar_(0.0) { siec_ = new Siec(); }
  ~Symulacja() {}

  void run();
  double PobierzStanZegara() { return zegar_; }

  void DodajDoKalendarza(Zdarzenie* zd) { kalendarz_->push(zd); }
  void UsunZKalendarza() { kalendarz_->pop(); }
  Zdarzenie* PobierzPierwszyElement() { kalendarz_->top(); }

private:
  double zegar_;

  Siec* siec_;

  priority_queue<Zdarzenie*, vector<Zdarzenie*>, decltype(comparer)>* kalendarz_;
};

#endif // !CSMA_PP_SYMULACJA_H
