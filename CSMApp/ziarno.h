#ifndef CSMA_PP_ZIARNO_H
#define CSMA_PP_ZIARNO_H

#include "generator_rownomierny.h"
#include <fstream>
#include <iostream>

class Ziarno 
{
public:
  Ziarno() : odstep_ziaren_(100000), liczba_ziaren_(100) {}
  ~Ziarno() {}
  void GeneracjaZiaren();

private:
  int odstep_ziaren_;
  int liczba_ziaren_;
  GenRownomierny* uniform_;
};

#endif // !CSMA_PP_ZIARNO_H
