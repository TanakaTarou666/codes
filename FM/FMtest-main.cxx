#include"../src/tensor.h"
#include"../src/vector3d.h"

int main(){
	
  Tensor V(2,4,3,1.0);
  Vector3d Vd(2,4,3,1.0);
  double count;
  for(int k=0;k<2;k++){
    count =1.0;
    for(int i=0;i<4;i++){
      for(int j=0;j<3;j++){
        if(k==0){
          Vd[k][i][j] = count;
          V[k](i,j) = count;
          count++;
        }else if (k==1){
          Vd[k][i][j] = count*2;
          V[k](i,j) = count*2;
          count++;
        }
      }
    }
  }
  Tensor U(2,5,3,1.0);
  Vector3d Ud(2,5,3,1.0);
  for(int k=0;k<2;k++){
    count =1.0;
    for(int i=0;i<5;i++){
      for(int j=0;j<3;j++){
        if(k==0){
          Ud[k][i][j] = count;
          U[k](i,j) = count;
          count++;
        }else if (k==1){
          Ud[k][i][j] = count*2;
          U[k](i,j) = count*2;
          count++;
        }
      }
    }
  }

  Tensor C(2,5,4,1.0);
  Vector3d Cd(2,5,4,1.0);
  for(int k=0;k<2;k++){
    count =1.0;
    for(int i=0;i<5;i++){
      for(int j=0;j<4;j++){
        if(k==0){
          Cd[k][i][j] = count;
          C[k](i,j) = count;
          count++;
        }else if (k==1){
          Cd[k][i][j] = count*2;
          C[k](i,j) = count*2;
          count++;
        }
      }
    }
  }
      std::cout << "U:\n" << U << std::endl;
      std::cout << "V:\n" << V << std::endl;

      Cd = all(Cd,0.0);
      std::cout << "C:\n" << Cd << std::endl;

    Vector count_U(Ud.rows(),1,"all");
      count_U = all(count_U,0.0);
      std::cout << "U_c:\n" << count_U << std::endl;

     // std::fill(count_U[0], count_U[Ud.rows()], 0);
      //std::fill(count_V[0], count_V[Ud.rows()], 0);
  /*
  Tensor prev_U(2,5,3, 0.0);
  Vector3d prev_Ud(2,5,3, 0.0);
  Vector3d prev_Vd(2,4,3, 0.0);
  double err,miss=0.0;
  for(int k=0;k<1;k++){
      for(int i=0;i<5;i++){
        for(int j=0;j<4;j++){
          err = U[k][i]*U[k][i];
          std::cout << "err:" << err << std::endl;
          miss = 0.0;
          for(int d=0;d<3;d++){
          miss += U[k][i][d]*U[k][i][d];
          
          prev_U[k](i,d)+=tensor_mul(V,V,U,k,d,i,j);
          prev_Ud[k][i][d]+=vector3d_mul(Vd,Vd,Ud,k,d,i,j);
          prev_Vd[k][j][d]+=vector3d_mul(Ud,Ud,Vd,k,d,j,i);
          }
          std::cout << "miss:" << miss << std::endl;
        }
      }
      std::cout << "prev_Ud.cols():\n" << prev_Ud.cols() << std::endl;
      std::cout << "prev_U:\n" << prev_U[k] << std::endl;
      std::cout << "prev_Ud:\n" << prev_Ud[k] << std::endl;
      std::cout << "prev_Ud:\n" << prev_Vd[k] << std::endl;
  }
  
  std::cout << "--------------------------------------------------------------------------" << std::endl;

  Tensor prev_U_CV(2,5,3, 0.0);
  Vector3d prev_U_CV_d(2,5,3, 0.0);
  for(int k=0;k<1;k++){
      for(int i=0;i<5;i++){
        for(int j=0;j<4;j++){
          for(int d=0;d<3;d++){
          prev_U_CV[k](i,d) += C[k](i,j)*V[k](j,d);
          prev_U_CV_d[k][i][d] += Cd[k][i][j]*Vd[k][j][d];
          }
        }
      }
      std::cout << "prev_U:\n" << prev_U_CV[k] << std::endl;
      std::cout << "prev_U:\n" << prev_U_CV_d[k] << std::endl;
  }

  Tensor prev_V_UC(2,4,3, 0.0);
  Vector3d prev_V_UC_d(2,4,3, 0.0);
  for(int k=0;k<1;k++){
      for(int i=0;i<5;i++){
        for(int j=0;j<4;j++){
          for(int d=0;d<3;d++){
          prev_V_UC[k](j,d) += U[k](i,d)*C[k](i,j);
          prev_V_UC_d[k][j][d] += Ud[k][i][d]*Cd[k][i][j];
          }
        }
      }
      std::cout << "prev_V:\n" << prev_V_UC[k] << std::endl;
      std::cout << "prev_V:\n" << prev_V_UC_d[k] << std::endl;
  }
  */
  return 0;
}
