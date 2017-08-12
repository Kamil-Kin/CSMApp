#ifndef CSMA_PP_ZIARNO_H
#define CSMA_PP_ZIARNO_H

#include "generator_rownomierny.h"
#include <fstream>
#include <iostream>

class Ziarno 
{
public:
  Ziarno() : odstep_ziaren_(100000), liczba_ziaren_(200) { new GenRownomierny(1); }
  ~Ziarno() {}

  void GeneracjaZiaren();

private:
  int odstep_ziaren_;
  int liczba_ziaren_;
  int ziarna[200];
  GenRownomierny* uniform_;
};

#endif // !CSMA_PP_ZIARNO_H
