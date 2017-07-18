#include "symulacja.h"
#include "nadajnik.h"
#include <cstdlib>
#include <ctime>

void Symulacja::run() 
{
  srand(time(NULL));

  nad_->NowyPakiet(1);
  nad_->NowyPakiet(4);



}