#include"sparseVector.h"
#include"matrix.h"

#ifndef __SPARSEMATRIX__
#define __SPARSEMATRIX__

class SparseMatrix{
 private:
  //行数，列数
  int Rows, Cols;
  //SparseVector *Element;
 public:
  SparseVector *Element;
  //コンストラクタ
  SparseMatrix(int rows=0, int cols=0);
  //コピーコンストラクタ
  SparseMatrix(const SparseMatrix &arg);
  //ムーブコンストラクタ
  SparseMatrix(SparseMatrix &&arg);
  explicit SparseMatrix(const Vector &arg, const char *s);
  //デストラクタ
  ~SparseMatrix(void);
  //コピー代入
  SparseMatrix &operator=(const SparseMatrix &arg);
  //ムーブ代入
  SparseMatrix &operator=(SparseMatrix &&arg);
  //Rowを返す
  int rows(void) const;
  //Colsを返す
  int cols(void) const;
  SparseVector operator[](int index) const{ return Element[index];}
  SparseVector &operator[](int index){ return Element[index];}
  SparseMatrix operator+(void) const;
  SparseMatrix operator-(void) const;
};

Matrix operator*(const SparseMatrix &lhs, const Matrix &rhs);

std::ostream &operator<<(std::ostream &os, const SparseMatrix &rhs);
bool operator==(const SparseMatrix &lhs, const SparseMatrix &rhs);
double frobenius_norm(const SparseMatrix &arg);
Matrix Hadamard(const SparseMatrix &lhs, const Matrix &rhs);
Matrix M_Hadamard(const Matrix &lhs, const Matrix &rhs);

SparseMatrix S_Hadamard(const SparseMatrix &lhs, const Matrix &rhs);
SparseMatrix S_Hadamard(const Matrix &lhs, const Matrix &rhs);
SparseMatrix S_Hadamard(const Matrix &lhs, const Matrix &rhs,SparseMatrix &result);
SparseMatrix S_Hadamard(const SparseMatrix &lhs, const Matrix &rhs,SparseMatrix &result);
Matrix transpose(const SparseMatrix &arg);

#endif
