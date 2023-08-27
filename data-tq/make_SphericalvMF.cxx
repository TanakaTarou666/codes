/*******************************
3混合vonMisesFisher分布

vonMisesFisher分布
http://d.hatena.ne.jp/ryamada22/searchdiary?word=%2A%5B%CA%FD%B8%FE%C5%FD%B7%D7%B3%D8%5D

mu:中心
分散の逆数に相当すると思われるパラメータkappaは大きいほど分布が狭まる。

mu0:(0.3,0.3,0.91)
mu1:(0.3,0.91,0.3)
mu2:(0.91,0.3,0.3)
 *******************************/
#include<iostream>
#include<cstdlib>
#include<cmath>
#include"../src/vector.h"
#include"../src/matrix.h"

const Matrix vonMisesFisher3(const int &n, const Vector &mu, const double &kappa);
const Vector outerProduct3(const Vector &lhs, const Vector &rhs);

int main(void){
  Matrix mu(4,3);
  Matrix x_c(10,2);
  mu[0][0]=0.3; mu[0][1]=0.35; mu[0][2]=sqrt(1.0-0.3*0.3-0.35*0.35);
  //mu[1][0]=0.3; mu[1][1]=0.2; mu[1][2]=sqrt(1.0-0.3*0.3-0.2*0.2);
  mu[1][0]=0.3; mu[1][1]=sqrt(1.0-0.3*0.3-0.35*0.35); mu[1][2]=0.35;
  mu[2][0]=sqrt(1.0-0.3*0.3-0.3*0.3); mu[2][1]=0.3; mu[2][2]=0.3;
  mu[3][0]=0.5; mu[3][1]=0.5; mu[3][2]=0.5;
  int c = 0;
  for(int i=0;i<2;i++){
    Matrix x=vonMisesFisher3(5, mu[i], 16.0E+1);
    //if(i == 2)
      //Matrix b = x;
    //if(i != 1){
    for(int k=0;k<5;k++){
      std::cout << x[k][0] << "," << x[k][1] << "\t" << x[k][2] << std::endl;
      x_c[c][0] = x[k][0];
      x_c[c][1] = x[k][1];
      c++;
    }
    //}
    std::cout << c <<"\n" << std::endl;
  }

  for(int k=0;k<10;k++){
      for(int i=0;i<10;i++){
        std::cout << x_c[k][0] << "\t" << x_c[i][1] << "\t" << sqrt(1-(pow(x_c[i][1],2)+pow(x_c[k][0],2))) << std::endl;
      }
    }
  std::cout <<"----------" << std::endl;
  for(int k=0;k<10;k++){
      std::cout << x_c[k][0] << "," ;
    }
    std::cout << "\n" ;
  for(int i=0;i<10;i++){
        std::cout << x_c[i][1] << "," ;
    }
    std::cout << "\n" ;
  std::cout <<"----------" << std::endl;
  int count = 0;
  for(int k=0;k<10;k++){
        std::cout << "10" ;
        count = 0;
      for(int i=0;i<10;i++){
        std::cout << " " << count << " " << sqrt(1-(pow(x_c[i][1],2)+pow(x_c[k][0],2))) ;
        count++;
      }
      std::cout <<"\n";
    }

  return 0;
}
//50 → 10

const Vector outerProduct3(const Vector &lhs, const Vector &rhs){
  Vector result(3);
  result[0]=lhs[1]*rhs[2]-lhs[2]*rhs[1];
  result[1]=lhs[2]*rhs[0]-lhs[0]*rhs[2];
  result[2]=lhs[0]*rhs[1]-lhs[1]*rhs[0];
  return result;
}


const Vector quaternionProduct(const Vector &lhs, const Vector &rhs){
  if(lhs.size()!=4 || rhs.size()!=4){
    std::cerr << "quaterinonPriduct::Error" << std::endl;
    exit(1);
  }
  double a=lhs[0], b=rhs[0];
  Vector U(3), V(3);
  U[0]=lhs[1]; U[1]=lhs[2]; U[2]=lhs[3];
  V[0]=rhs[1]; V[1]=rhs[2]; V[2]=rhs[3];
  Vector result(4);
  result[0]=a*b-U*V;
  Vector tmp=a*V+b*U+outerProduct3(U,V);
  result[1]=tmp[0];
  result[2]=tmp[1];
  result[3]=tmp[2];
  return result;
}

const Matrix vonMisesFisher3(const int &n, const Vector &mu, const double &kappa) {
  //n:個数
  //mu:平均
  //kappa:分散の逆数

  //まずは(1,0,0)を中心、精度をkappaとするVMF
  double c=2.0/kappa*sinh(kappa);
#ifdef DEBUG
  std::cout << "c:" << c << std::endl;
#endif
  Vector y(n);
  for(int k=0;k<n;k++){
    y[k]=rand()/(double)RAND_MAX;
  }
#ifdef DEBUG
  std::cout << "y:\n" << y << std::endl;
#endif
  Vector w(n);
  for(int k=0;k<n;k++){
    w[k]=1.0/kappa*log(exp(-kappa)+kappa*c*y[k]);
  }
#ifdef DEBUG
  std::cout << "w:\n" << w << std::endl;
#endif
  Vector theta(n);
  for(int k=0;k<n;k++){
    theta[k]=2.0*M_PI*(rand()/(double)RAND_MAX);
  }
#ifdef DEBUG
  std::cout << "theta:\n" << theta << std::endl;
#endif
  Matrix tmpResult(n, 3);
  for(int k=0;k<n;k++){
    tmpResult[k][0]=w[k];
    tmpResult[k][1]=sqrt(1.0-w[k]*w[k])*cos(theta[k]);
    tmpResult[k][2]=sqrt(1.0-w[k]*w[k])*sin(theta[k]);
  }
  //中心(1,0,0)に対するVMFが得られた。
  //  return tmpResult;
#ifdef DEBUG
  std::cout << "tmpResult:\n" << tmpResult << std::endl;
#endif

  //muと(1,0,0)との回転角
  Vector from(mu);
  Vector to(3);
  to[0]=1.0;
  to[1]=0.0;
  to[2]=0.0;
  Vector alphaBetaGamma;//set later
  if(squared_norm(from-to)<1.0E-15){
    alphaBetaGamma=to;
  }
  else{
    alphaBetaGamma=outerProduct3(from, to);
  }
#ifdef DEBUG
  std::cout << "alphaBetaGamma before normalized:" << alphaBetaGamma << std::endl;
#endif
  alphaBetaGamma/=squared_norm(alphaBetaGamma);
  double cosTheta=from*to;
  double cosThetaHalf=sqrt(0.5*(1.0+cosTheta));
  double sinThetaHalf=sqrt(0.5*(1.0-cosTheta));
  //回転角の半分に対応する正弦、余弦が得られた。
#ifdef DEBUG
  std::cout << "cosThetaHalf:" << cosThetaHalf << "\t" << "sinThetaHalf:" << sinThetaHalf << std::endl;
#endif

#ifdef DEBUG
  std::cout << "alphaBetaGamma:" << alphaBetaGamma << std::endl;
#endif

  //回転
  Vector Q(4), R(4);
  Q[0]=cosThetaHalf;
  Q[1]=alphaBetaGamma[0]*sinThetaHalf;
  Q[2]=alphaBetaGamma[1]*sinThetaHalf;
  Q[3]=alphaBetaGamma[2]*sinThetaHalf;
  R[0]=cosThetaHalf;
  R[1]=-alphaBetaGamma[0]*sinThetaHalf;
  R[2]=-alphaBetaGamma[1]*sinThetaHalf;
  R[3]=-alphaBetaGamma[2]*sinThetaHalf;

  for(int k=0;k<n;k++){
    Vector P(4);
    P[0]=0.0;
    P[1]=tmpResult[k][0];
    P[2]=tmpResult[k][1];
    P[3]=tmpResult[k][2];
    Vector tmp=quaternionProduct(R,quaternionProduct(P, Q));
    Vector result(4);
    result[0]=tmp[1];
    result[1]=tmp[2];
    result[2]=tmp[3];
    tmpResult[k]=result;
  }

  return tmpResult;
}

