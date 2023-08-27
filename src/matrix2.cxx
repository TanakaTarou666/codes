#include<iostream>
#include"matrix2.h"
#include"vector.h"
#include<cmath>

Matrix2::Matrix2(void): Rows(0), Cols(0), Element(NULL){
}

Matrix2::Matrix2(int rows, int cols) try : Rows(rows), Cols(cols), Element(new double[Rows*Cols]){
}
catch(std::bad_alloc){
  std::cerr << "Matrix2::Matrix2(int, int): Out of Memory" << std::endl;
  throw;
 }

Matrix2::Matrix2(const Matrix2 &arg) try : Rows(arg.Rows),
					  Cols(arg.Cols),
					  Element(new double[Rows*Cols]){
  for(int i=0;i<Rows*Cols;i++){
    Element[i]=arg.Element[i];
  }
					}
catch(std::bad_alloc){
  std::cerr << "Matrix2::Matrix2(int, int): Out of Memory" << std::endl;
  throw;
 }

Matrix2::Matrix2(Matrix2 &&arg)
  : Rows(arg.Rows), Cols(arg.Cols), Element(arg.Element){
  arg.Rows=0;
  arg.Cols=0;
  arg.Element=nullptr;
}

Matrix2 &Matrix2::operator=(const Matrix2 &rhs){
  if(this!=&rhs){
    if(Rows!=rhs.Rows || Cols!=rhs.Cols){
      Rows=rhs.Rows;
      Cols=rhs.Cols;
      delete []Element;
      try{
	Element=new double[Rows*Cols];
      }
      catch(std::bad_alloc){
	throw;
      }
    }//if(Rows!=rhs.Rows || Cols!=rhs.Cols){
    for(int i=0;i<Rows*Cols;i++){
      Element[i]=rhs.Element[i];
    }
  }
  return *this;
}

Matrix2 &Matrix2::operator=(Matrix2 &&arg){
  if(this!=&arg){
    Rows=arg.Rows;
    Cols=arg.Cols;
    delete []Element;
    Element=arg.Element;
    arg.Rows=0;
    arg.Cols=0;
    arg.Element=nullptr;
  }
  return *this;
}

Matrix2::~Matrix2(void){
  delete [] Element;
  return;
}

int Matrix2::rows(void) const{
  return Rows;
}

int Matrix2::cols(void) const{
  return Cols;
}

Vector Matrix2::operator[](int index) const{
  Vector result(Cols);
  for(int col=0;col<Cols;col++){
    result[col]=Element[Cols*index+col];
  }  
  return result;
}

double &Matrix2::operator()(int row, int col){
  return Element[row*Cols+col];
}

double Matrix2::operator()(int row, int col) const{
  return Element[row*Cols+col];
}

Matrix2 Matrix2::operator+(void) const{
  return *this;
}

Matrix2 Matrix2::operator-(void) const{
  Matrix2 result(*this);
  for(int i=0;i<Rows*Cols;i++){
    result.Element[i]*=-1.0;
  }
  return result;
}


Matrix2 &Matrix2::operator+=(const Matrix2 &rhs){
  if(Rows!=rhs.Rows || Cols!=rhs.Cols){
    std::cerr << "Matrix2::operator+=: Size Unmatched" << std::endl;
    exit(1);
  }
  for(int i=0;i<Rows*Cols;i++){
    Element[i]+=rhs.Element[i];
  }
  return *this;
}

Matrix2 &Matrix2::operator-=(const Matrix2 &rhs){
  if(Rows!=rhs.Rows || Cols!=rhs.Cols){
    std::cerr << "Matrix2::operator-=: Size Unmatched" << std::endl;
    exit(1);
  }
  for(int i=0;i<Rows*Cols;i++){
    Element[i]-=rhs.Element[i];
  }
  return *this;
}

std::ostream &Matrix2::print(std::ostream &lhs) const{
  lhs << "(";
  int i;
  for(int row=0;row<Rows-1;row++){
    lhs << "(";
    for(int col=0;col<Cols;col++){
      lhs << Element[row*Cols+col] << ", ";
    }
    lhs << ")" << std::endl;
  }
  lhs << "(";
  for(int col=0;col<Cols;col++){
    lhs << Element[(Rows-1)*Cols+col] << ", ";
  }
  lhs << "))";
  return lhs;
}

std::ostream &operator<<(std::ostream &lhs, const Matrix2 &rhs){
  return rhs.print(lhs);
}

Matrix2 operator+(const Matrix2 &lhs, const Matrix2 &rhs){
  Matrix2 result(lhs);
  return (result+=rhs);
}

Matrix2 operator-(const Matrix2 &lhs, const Matrix2 &rhs){
  Matrix2 result(lhs);
  return (result-=rhs);
}

Matrix2 operator*(double factor, const Matrix2 &rhs){
  if(rhs.rows()==0 || rhs.cols()==0){
    std::cerr << "operator*(double , const Matrix2 &): Size unmatched"
	      << std::endl;
    exit(1);
  }
  Matrix2 result(rhs);
  for(int row=0;row<result.rows();row++){
    for(int col=0;col<result.cols();col++){
      result(row,col)*=factor;
    }
  }
  return result;
}


Vector operator*(const Matrix2 &lhs, const Vector &rhs){
  if(lhs.cols()!=rhs.size() || lhs.rows()==0){
    std::cerr << "operator*(const Matrix2 &, const Vector &): Size unmatched"
	      << std::endl;
    exit(1);
  }
  Vector result(lhs.rows());
  for(int row=0;row<lhs.rows();row++){
    result[row]=0.0;
    for(int col=0;col<lhs.cols();col++){
      result[row]+=lhs(row,col)*rhs[col];
    }
  }
  return result;
}

Matrix2 operator*(const Matrix2 &lhs, const Matrix2 &rhs){
  if(lhs.cols()!=rhs.rows() || lhs.rows()==0 || rhs.cols()==0){
    std::cerr << "operator*(const Matrix2 &, const Matrix2 &): Size unmatched"
	      << std::endl;
    exit(1);
  }
  Matrix2 result(lhs.rows(), rhs.cols());
  for(int row=0;row<result.rows();row++){
    for(int col=0;col<result.cols();col++){
      result(row,col)=0.0;
    }
  }
  for(int row=0;row<result.rows();row++){
    for(int col=0;col<result.cols();col++){
      for(int k=0;k<lhs.cols();k++){
	result(row,col)+=lhs(row,k)*rhs(k,col);
      }
    }
  }
  return result;
}

bool operator==(const Matrix2 &lhs, const Matrix2 &rhs){
  if(lhs.rows()!=rhs.rows() || lhs.cols()!=rhs.cols()){
    return false;
  }
  for(int row=0;row<lhs.rows();row++){
    for(int col=0;col<lhs.cols();col++){
      if(lhs(row,col)!=rhs(row,col)){
	  return false;
      }
    }
  }
  return true;
}

bool operator!=(const Matrix2 &lhs, const Matrix2 &rhs){
  if(lhs.rows()!=rhs.rows() || lhs.cols()!=rhs.cols()){
    return true;
  }
  for(int row=0;row<lhs.rows();row++){
    for(int col=0;col<lhs.cols();col++){
      if(lhs(row,col)!=rhs(row,col)){
	  return true;
      }
    }
  }
  return false;
}

double frobenius_norm(const Matrix2 &arg){
  double result=0.0;
  for(int i=0;i<arg.rows();i++){
    for(int j=0;j<arg.cols();j++){
      result+=arg(i,j)*arg(i,j);
    }}
  return sqrt(result);
}

Matrix2 transpose(const Matrix2 &arg){
  if(arg.rows()==0 || arg.cols()==0){
    std::cerr << "transpose(const Matrix): zero-sized matrix" << std::endl;
  }
  Matrix2 result(arg.cols(), arg.rows());
  for(int i=0;i<result.rows();i++){
    for(int j=0;j<result.cols();j++){
      result(i,j)=arg(j,i);
    }
  }
  return result;
}


Matrix matrix2_to_matrix(const Matrix2 &arg){
  Matrix result(arg.rows(),arg.cols());
  if(arg.rows()<1 || arg.cols()<1){
    std::cout << "matrix2_to_matrix:";
    std::cout << "Can't calculate innerproduct ";
    std::cout << "for 0-sized vector ";
    std::cout << "or for different sized vector:";
    std::cout << "arg.Cols=" << arg.cols() << ", ";
    std::cout << "arg.Rows=" << arg.rows();
    std::cout << std::endl;
    exit(1);
  }
  for(int i=0;i<arg.rows();i++){
    for(int j=0;j<arg.cols();j++){
      result[i][j]=arg(i,j);
    }
  }
  return result;
}
