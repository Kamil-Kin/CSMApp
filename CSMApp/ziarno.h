#ifndef CSMA_PP_ZIARNO_H
#define CSMA_PP_ZIARNO_H

#include "generator_rownomierny.h"
#include <fstream>
#include <iostream>

using std::fstream;
using std::cout;
using std::endl;
using std::ios;


class Ziarno 
{
public:
  Ziarno();
  ~Ziarno();

  void GeneracjaZiaren();
  int PobierzZiarno(int index);
private:
  int odstep_ziaren_;
  int liczba_ziaren_;
  int ziarna[400];
  GenRownomierny* uniform_;
};

#endif // !CSMA_PP_ZIARNO_H
