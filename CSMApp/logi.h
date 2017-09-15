#ifndef CSMA_PP_LOGI_H
#define CSMA_PP_LOGI_H

#include <iostream>

using std::cout;
using std::endl;

class Logi
{
public:
  Logi() {}
  ~Logi() {}

  void WypiszLogi(int faza, long id, double czas, int nr);
};

#endif // !CSMA_PP_LOGI_H
