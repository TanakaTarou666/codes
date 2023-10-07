#include"sparseVector.h"
#include"sparseMatrix.h"
#include"matrix.h"

//コンストラクタ
SparseMatrix::SparseMatrix(int rows, int cols) try :
  Rows(rows), Cols(cols), Element(new SparseVector[Rows]){
  }
catch(std::bad_alloc){
  std::cerr << "Out of Memory" << std::endl;
  throw;
 }

//コピーコンストラクタ
SparseMatrix::SparseMatrix(const SparseMatrix &arg) try :
  Rows(arg.Rows), Cols(arg.Cols), Element(new SparseVector[Rows]){
    for(int i=0;i<Rows;i++)
      Element[i]=arg.Element[i];
  }
catch(std::bad_alloc){
  std::cerr << "Out of Memory" << std::endl;
  throw;
 }

//ムーブコンストラクタ
SparseMatrix::SparseMatrix(SparseMatrix &&arg)
  : Rows(arg.Rows), Cols(arg.Cols), Element(arg.Element){
  arg.Rows=0;
  arg.Cols=0;
  arg.Element=nullptr;
}

// SparseMatrix::SparseMatrix(const Vector &arg, const char *s) try : 
// Rows(arg.size()), Cols(arg.size()), Element(new SparseVector[arg.size()]){
//   if(strcmp(s, "diag")!=0){
//       std::cerr << "Invalid string parameter" << std::endl;
//       exit(1);
//   }
//     for(int i=0;i<Rows;i++){
// 	      Element[i].Element[0]=arg[i];
//         Element[i].Index[0]=i;
//     }
// }
// catch(std::bad_alloc){
//   std::cerr << "Out of Memory" << std::endl;
//   throw;
//  }

//デストラクタ
SparseMatrix::~SparseMatrix(void){
  delete []Element;
}

//コピー代入
SparseMatrix &SparseMatrix::operator=(const SparseMatrix &arg){
  if(this==&arg)	return *this;
  //Rows=arg.Rows;ここではRowsを更新してはいけない
  if(this->Rows != arg.Rows || this->Cols != arg.Cols){
    Rows=arg.Rows;
    Cols=arg.Cols;
    delete []Element;
    try{
      Element=new SparseVector[Rows];
    }
    catch(std::bad_alloc){
      std::cerr << "Out of Memory" << std::endl;
      throw;
    }
  }
  for(int i=0;i<Rows;i++)
    Element[i]=arg.Element[i];
  return *this;
}

//ムーブ代入
SparseMatrix &SparseMatrix::operator=(SparseMatrix &&arg){
  if(this==&arg){
    return *this;
  }
  else{
    Rows=arg.Rows;
    Cols=arg.Cols;
    delete []Element;
    Element=arg.Element;
    arg.Rows=0;
    arg.Cols=0;
    arg.Element=nullptr;
    return *this;
  }
}

int SparseMatrix::rows(void) const{
  return Rows;
}

int SparseMatrix::cols(void) const{
  return Cols;
}

/*SparseVector SparseMatrix::operator[](int index) const{
  return Element[index];
}

SparseVector &SparseMatrix::operator[](int index){
  return Element[index];
}
*/
SparseMatrix SparseMatrix::operator+(void) const{
  return *this;
}

SparseMatrix SparseMatrix::operator-(void) const{
  SparseMatrix result=*this;
  for(int i=0;i<result.Rows;i++){
    result[i]=-result[i];
  }
  return result;
}

Matrix operator*(const SparseMatrix &lhs, const Matrix &rhs){
  if(lhs.rows()<1 || rhs.cols()<1 || lhs.cols()!=rhs.rows()){
    std::cout << "Can't calculate innerproduct";
    std::cout << "for 0-sized vector";
    std::cout << "or for different sized vector";
    std::cout << std::endl;
    exit(1);
  }
  int n=lhs.rows();
  int m=lhs.cols();
  int l=rhs.cols();
  Matrix result(n, l);
  for(int i=0;i<n;i++){
    for(int j=0;j<l;j++){
      result[i][j]=0.0;
    }
      for(int k=0;k<lhs[i].essencialSize();k++){
        for(int j=0;j<l;j++){
	      result[i][j]+=lhs.Element[i].Element[k]*rhs[lhs.Element[i].Index[k]][j];
      }
    }
  }
  return result;
}

std::ostream &operator<<(std::ostream &os, const SparseMatrix &rhs){
  os << "(";
  if(rhs.rows()>0){
    for(int i=0;;i++){
      os << rhs[i];
      if(i>=rhs.rows()-1) break;
      os << "\n";
    }
  }
  os << ')';
  return os;
}

bool operator==(const SparseMatrix &lhs, const SparseMatrix &rhs){
  if(lhs.rows()!=rhs.rows())	return false;
  for(int i=0;i<lhs.rows();i++){
    if(lhs[i]!=rhs[i])	return false;
  }
  return true;
}

double frobenius_norm(const SparseMatrix &arg){
  double result=0.0;
  for(int i=0;i<arg.rows();i++){
    result+=norm_square(arg[i]);
  }
  return sqrt(result);
}

//注意：本来のアダマール積と異なり、値が０の部分は計算していない
Matrix Hadamard(const SparseMatrix &lhs, const Matrix &rhs){
  Matrix result(rhs.rows(), rhs.cols(),0.0);
  for(int i=0;i<result.rows();i++){
    for(int j=0;j<lhs[i].essencialSize();j++){
        if(lhs[i].elementIndex(j) != 0)
  	      result[i][lhs[i].indexIndex(j)]=lhs[i].elementIndex(j)*rhs[i][lhs[i].indexIndex(j)];
    }
  }
  return result;
}

Matrix M_Hadamard(const Matrix &lhs, const Matrix &rhs){
  Matrix result(rhs.rows(), rhs.cols(),0.0);
  for(int i=0;i<result.rows();i++){
    for(int j=0;j<result.cols();j++){
        if(lhs[i][j] != 0)
  	      result[i][j]=lhs[i][j]*rhs[i][j];
    }
  }
  return result;
}

SparseMatrix S_Hadamard(const SparseMatrix &lhs, const Matrix &rhs){
  SparseMatrix result(rhs.rows(), rhs.cols());
  int lowsNum;
  for(int i=0;i<result.rows();i++){
    lowsNum=0;
    int a[lhs[i].essencialSize()+1];
    a[0]=0; 
    for(int j=0;j<lhs[i].essencialSize();j++){
      if(lhs[i].elementIndex(j) != 0 && rhs[i][lhs[i].indexIndex(j)]!=0) lowsNum++;
      a[j+1]=lowsNum;
    }
    SparseVector sv(rhs.cols(),lowsNum);
    for(int j=0;j<lhs[i].essencialSize();j++){
      if(a[j]!=a[j+1])
  	    sv.modifyElement(a[j],lhs[i].indexIndex(j),lhs[i].elementIndex(j)*rhs[i][lhs[i].indexIndex(j)]);
    }
    result[i] = sv;
  }
  return result;
}

SparseMatrix S_Hadamard(const Matrix &lhs, const Matrix &rhs){
  int n=rhs.rows(),m=rhs.cols();
  SparseMatrix result(n, m);
  int lowsNum;
  for(int i=0;i<n;i++){
    lowsNum=0;
    int a[2][m+1];
    a[0][0]=0;
    a[1][0]=0;  
    for(int j=0;j<m;j++){
      a[0][j+1]=j+1;
      if(lhs[i][j] != 0 && rhs[i][j]!=0) lowsNum++;
      a[1][j+1]=lowsNum;
    }
    SparseVector sv(m,lowsNum);
    for(int j=0;j<m;j++){
      if(a[1][j]!=a[1][j+1])
  	    sv.modifyElement(a[1][j],a[0][j],lhs[i][j]*rhs[i][j]);
    }
    result[i] = sv;
 
  }
  
  return result;
}

SparseMatrix S_Hadamard(const Matrix &lhs, const Matrix &rhs,SparseMatrix &result){
  int n=rhs.rows(),m=rhs.cols();
  for(int i=0;i<n;i++){
    int k=0;
    for(int j=0;j<m;j++){
      if(lhs[i][j]!=0 && rhs[i][j]!=0){
  	    //result[i].modifyElement(k,j,lhs[i][j]*rhs[i][j]); 
        result.Element[i].Element[k]=lhs.Element[i].Element[j]*rhs.Element[i].Element[j];
        result.Element[i].Index[k]=j;
        k++;
      }
    }
  }
  return result;
}

SparseMatrix S_Hadamard(const SparseMatrix &lhs, const Matrix &rhs,SparseMatrix &result){
  int n=rhs.rows();
  for(int i=0;i<n;i++){
    for(int j=0;j<lhs.Element[i].essencialSize();j++){
        result.Element[i].Element[j]=lhs.Element[i].Element[j]*rhs.Element[i].Element[lhs.Element[i].Index[j]];
        result.Element[i].Index[j]=lhs.Element[i].Index[j];
     }
  }
  return result;
}

Matrix transpose(const SparseMatrix &arg){
  Matrix result(arg.cols(), arg.rows());
  for(int i=0;i<result.cols();i++){
    for(int j=0;j<arg[i].essencialSize();j++){
      result[arg.Element[i].indexIndex(j)][i]=arg.Element[i].Element[j];
    }
  }
  return result;
}