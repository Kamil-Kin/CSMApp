#ifndef CSMA_PP_LOGI_H
#define CSMA_PP_LOGI_H

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::fstream;
using std::ios;
using std::string;

class Logi
{
public:
  Logi() {}
  ~Logi() {}

  void WypiszLogi(int faza, int id, double czas, int nr);

  void UstawKolor(string numer);
};

#endif // !CSMA_PP_LOGI_H
