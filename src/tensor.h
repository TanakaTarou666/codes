#include<iostream>
#include<cstring>
#include"matrix2.h"

#ifndef __TENSOR__
#define __TENSOR__

class Tensor{
 private:
  int Heights;
  Matrix2 *Element;
 public:
  //Tensor(int rows=0);
  Tensor(int heights, int rows=0, int cols=0);
  Tensor(int heights, int rows, int cols, double arg);
  ~Tensor(void);
  Tensor(const Tensor &arg);
  Tensor &operator=(const Tensor &arg);
  Tensor(Tensor &&arg);
  Tensor &operator=(Tensor &&arg);
  int heights(void) const;
  Matrix2 operator[](int index) const;
  Matrix2 &operator[](int index);
};

std::ostream &operator<<(std::ostream &os, const Tensor &rhs);
bool operator==(const Tensor &lhs, const Tensor &rhs);
double frobenius_norm(const Tensor &arg);
Tensor operator-(const Tensor &lhs, const Tensor &rhs);
double tensor_mul(const Tensor &lhs, const Tensor &rhs, const Tensor &khs, double k , double d, double j);
double tensor_mul(const Tensor &lhs, const Tensor &rhs, const Tensor &khs, double k , double d, double i, double j);

#endif
