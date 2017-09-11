#ifndef CSMA_PP_GENERATOR_ROWNOMIERNY_H
#define CSMA_PP_GENERATOR_ROWNOMIERNY_H

class GenRownomierny
{
public:
  GenRownomierny(int ziarno): kernel_(ziarno)
  {
    M = 2147483647.0;
    A = 16807;
    Q = 127773;
    R = 2836;
  } 
  ~GenRownomierny() {}

  double Generacja01();
  double GeneracjaR(double dol, double gora);
  int getKernel() { return kernel_; }
private:
  double M;
  int A;
  int Q;
  int R;
  int kernel_;
};

#endif // !CSMA_PP_GENERATOR_ROWNOMIERNY_H
