#ifndef CSMA_PP_SIEC_H
#define CSMA_PP_SIEC_H

#include "zdarzenie.h"
#include <vector>
#include <queue>

//class Zdarzenie;
class Nadajnik;
class Kanal;

using namespace std;

const auto comparer = [](Zdarzenie* z1, Zdarzenie* z2) {
  return z1->pobierz_czas_zd() > z2->pobierz_czas_zd(); };

class Siec 
{
public:
  Siec();
  ~Siec();
  void DodajDoKalendarza(Zdarzenie* zd) { kalendarz_->push(zd); }
  void UsunZKalendarza() { kalendarz_->pop(); }
  Zdarzenie* PobierzPierwszyElement() { kalendarz_->top(); }

private:
  const int kLiczbaNad_ = 4;
  vector<Nadajnik*> nadajniki_;
  Kanal* kanal_;

  priority_queue<Zdarzenie*, vector<Zdarzenie*>, decltype(comparer)>* kalendarz_;
};

#endif // !CSMA_PP_SIEC_H
