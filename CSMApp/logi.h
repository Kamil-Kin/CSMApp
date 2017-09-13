#ifndef CSMA_PP_LOGI_H
#define CSMA_PP_LOGI_H

#include <iostream>
//#include <string>
//#include <windows.h>
//#include <stdlib.h>

using std::cout;
using std::endl;
using std::ios;
using std::string;

class Logi
{
public:
  Logi() {}
  ~Logi() {}

  void WypiszLogi(int faza, long id, double czas, int nr);

  //void UstawKolor(string numer);
};

#endif // !CSMA_PP_LOGI_H
