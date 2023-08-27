#include<iostream>
#include<cstdlib>
#include<cmath>
#include"vector.h"
#include"tensor.h"

Tensor::Tensor(int heights, int rows, int cols) try :
  Heights(heights), Element(new Matrix2[Heights]){
  for(int i=0;i<Heights;i++){
    Element[i]=Matrix2(rows, cols);
  }
}
catch(std::bad_alloc){
    std::cerr << "Out of Memory" << std::endl;
    throw;
 }

//全ての要素をargで初期化
Tensor::Tensor(int heights, int rows, int cols, double arg) try :
  Heights(heights), Element(new Matrix2[Heights]){
    for(int i=0;i<Heights;i++){
    Element[i]=Matrix2(rows, cols);
    }
    for(int k=0;k<heights;k++){
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
	            Element[k][i][j]=arg;
              Element[k](i,j)=arg;
            }
        }
    }
  }
catch(std::bad_alloc){
  std::cerr << "Out of Memory" << std::endl;
  throw;
 }

double tensor_mul(const Tensor &lhs, const Tensor &rhs, const Tensor &khs, double k , double d, double j){
  // この関数では、計算結果のベクトルRのRijが出力される
  // プログラム上でDxNがNxDとなってるため，rowsではなくcols
  // k=嗜好数K, D=潜在次元数d
  double result_AAt;
  double result = 0.0;
  //A*At専用
  for(int d_i=0;d_i<rhs[k].cols();d_i++){
    result_AAt = 0;
    for(int i=0;i<lhs[k].rows();i++){
      //result_AAt +=lhs[k][i][d]*rhs[k][i][d_i];
      result_AAt +=lhs[k](i,d)*rhs[k](i,d_i);
      //std::cout << "resultAAt_t:" << result_AAt << std::endl;
    }
    //std::cout << "resultAAt:" << result_AAt << std::endl;
    //result += result_AAt*khs[k][j][d_i];//j行d_i列目
    result += result_AAt*khs[k](j,d_i);
  }
  return result;
}

double tensor_mul(const Tensor &lhs, const Tensor &rhs, const Tensor &khs, double k , double d, double i, double j){
  // この関数では、計算結果のベクトルRのRijが出力される
  // プログラム上でDxNがNxDとなってるため，rowsではなくcols
  // k=嗜好数K, D=潜在次元数d
  double result_AAt;
  double result = 0.0;
  //A*At専用
 for(int d_i=0;d_i<rhs[k].cols();d_i++){
    result_AAt = 0;
      //result_AAt +=lhs[k][i][d]*rhs[k][i][d_i];
      result_AAt +=lhs[k](j,d)*rhs[k](j,d_i);
      //std::cout << "resultAAt_t:" << result_AAt << std::endl;
    //std::cout << "resultAAt:" << result_AAt << std::endl;
    //result += result_AAt*khs[k][j][d_i];//j行d_i列目
    //std::cout << i << "," << j << "," << d << ":AAt:" << result_AAt << std::endl;
    result += result_AAt*khs[k](i,d_i);
    //std::cout << i << "," << j << "," << d << "::" << result << std::endl;
    //std::cout << i << "," << j << "," << d << ":AAt:" << result << std::endl;
 }
  return result;
}


Tensor::~Tensor(void){
  delete []Element;
}

Tensor::Tensor(const Tensor &arg) try :
  Heights(arg.Heights), Element(new Matrix2[Heights]){
  for(int i=0;i<Heights;i++){
    Element[i]=arg.Element[i];
  }
}
catch(std::bad_alloc){
    std::cerr << "Out of Memory" << std::endl;
    throw;
 }

Tensor::Tensor(Tensor &&arg)
  : Heights(arg.Heights), Element(arg.Element){
  arg.Heights=0;
  arg.Element=nullptr;
}

Tensor &Tensor::operator=(Tensor &&arg){
  if(this==&arg){
    return *this;
  }
  else{
    Heights=arg.Heights;
    delete []Element;
    Element=arg.Element;
    arg.Heights=0;
    arg.Element=nullptr;
    return *this;
  }
}

Tensor &Tensor::operator=(const Tensor &arg){
  if(this==&arg)	return *this;
  //Rows=arg.Rows;ここではRowsを更新してはいけない
  if(this->Heights != arg.Heights ){
    Heights=arg.Heights;
    delete []Element;
    try{
      Element=new Matrix2[Heights];
    }
    catch(std::bad_alloc){
      std::cerr << "Out of Memory" << std::endl;
      throw;
    }
  }
  for(int i=0;i<Heights;i++){
    Element[i]=arg.Element[i];
  }
  return *this;
}

int Tensor::heights(void) const{
  return Heights;
}

Matrix2 Tensor::operator[](int index) const{
  return Element[index];
}

Matrix2 &Tensor::operator[](int index){
  return Element[index];
}


std::ostream &operator<<(std::ostream &os, const Tensor &rhs){
  os << "(";
  if(rhs.heights()>0){
    for(int i=0;;i++){
      os << rhs[i];
      if(i>=rhs.heights()-1) break;
      os << "\n";
    }
  }
  os << ')';
  return os;
}

bool operator==(const Tensor &lhs, const Tensor &rhs){
  if(lhs.heights()!=rhs.heights())	return false;
  for(int i=0;i<lhs.heights();i++){
    if(lhs[i]!=rhs[i])	return false;
  }
  return true;
}


double frobenius_norm(const Tensor &arg){
  double result=0.0;
  for(int i=0;i<arg.heights();i++){
    result+=frobenius_norm(arg[i])*frobenius_norm(arg[i]);
  }
  return sqrt(result);
}



Tensor operator-(const Tensor &lhs, const Tensor &rhs){
  Tensor result(lhs);
  for(int i=0;i<result.heights();i++){
    result[i]=lhs[i]-rhs[i];
  }
  return result;
}
