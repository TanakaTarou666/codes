#include<iostream>
#include"vector.h"
#include"matrix.h"

#ifndef __MATRIX2__
#define __MATRIX2__

class Matrix2{
 private:
  int Rows, Cols;
  double* Element;
 public:
  Matrix2(void);
  Matrix2(int rows, int cols);
  Matrix2(const Matrix2 &arg);
  Matrix2 &operator=(const Matrix2 &rhs);
  Matrix2(Matrix2 &&arg);
  Matrix2 &operator=(Matrix2 &&arg);
  ~Matrix2(void);
  int rows(void) const;
  int cols(void) const;
  Vector operator[](int index) const;
  double &operator()(int row, int col);
  double operator()(int row, int col) const;
  Matrix2 operator+(void) const;
  Matrix2 operator-(void) const;
  Matrix2 &operator+=(const Matrix2 &rhs);
  Matrix2 &operator-=(const Matrix2 &rhs);
  std::ostream &print(std::ostream &lhs) const;
};

std::ostream &operator<<(std::ostream &lhs, const Matrix2 &rhs);
Matrix2 operator+(const Matrix2 &lhs, const Matrix2 &rhs);
Matrix2 operator-(const Matrix2 &lhs, const Matrix2 &rhs);
Vector operator*(const Matrix2 &lhs, const Vector &rhs);
Matrix2 operator*(const Matrix2 &lhs, const Matrix2 &rhs);
bool operator==(const Matrix2 &lhs, const Matrix2  &rhs);
bool operator!=(const Matrix2 &lhs, const Matrix2  &rhs);
Matrix2 operator*(double factor, const Matrix2 &rhs);
double frobenius_norm(const Matrix2 &arg);
Matrix2 transpose(const Matrix2 &arg);
Matrix matrix2_to_matrix(const Matrix2 &arg);

#endif
