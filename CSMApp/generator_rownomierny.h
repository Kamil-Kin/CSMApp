#ifndef CSMA_PP_GENERATOR_ROWNOMIERNY_H
#define CSMA_PP_GENERATOR_ROWNOMIERNY_H

class GenRownomierny 
{
public:
  GenRownomierny(int ziarno): kernel_(ziarno), dol(0.0), gora(0.0)
  {
    M = 2147483647.0;
    A = 16807;
    Q = 127773;
    R = 2836;
  } 
  ~GenRownomierny() {}

  int Generacja01();
  int GeneracjaR(double dol, double gora);
  int getKernel() { return kernel_; }
private:
  double M;
  int A;
  int Q;
  int R;
  int kernel_;
  double dol, gora;
};

#endif // !CSMA_PP_GENERATOR_ROWNOMIERNY_H
