#include"hcm.h"
#include"recom.h"

#define RBFKERNEL 1

#ifndef __RFCM__
#define __RFCM__

class RFCM: virtual public HCM{
protected:
  Matrix Kernel;
  //単位行列
  Matrix UnitMatrixData;
  //RBFカーネルのパラメータ
  double RBFsigma;
public:
  RFCM(int dimension,
       int data_number,
       int centers_number,
       double rbfsigma);
  double &rbfsigma(void);
  void copy_similarities(const Matrix &arg);
  virtual void revise_dissimilarities(void);
  void centersInitializePlusPlus(int random_index);
};
#endif
