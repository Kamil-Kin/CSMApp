#ifndef CSMA_PP_LOGI_H
#define CSMA_PP_LOGI_H

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::fstream;
using std::ios;

class Logi
{
public:
  Logi() {}
  ~Logi() {}

  void WypiszLogi(int faza, int id, double czas);
};

#endif // !CSMA_PP_LOGI_H
