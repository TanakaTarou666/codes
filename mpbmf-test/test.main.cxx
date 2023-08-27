#include"../src/tensor.h"
#include"../src/vector3d.h"

int main(){
	
  Tensor V(2,5,3,1.0);
  Vector3d Vd(2,5,3,1.0);
  double count;
  for(int k=0;k<2;k++){
    count =1.0;
    for(int i=0;i<5;i++){
      for(int j=0;j<3;j++){
        if(k==0){
          Vd[k][i][j] = 1.0;
          count++;
        }else if (k==1){
          Vd[k][i][j] = 2.0;
          count++;
        }
      }
    }
  }
  Tensor U(2,4,3,1.0);
  Vector3d Ud(2,4,3,1.0);
  for(int k=0;k<2;k++){
    count =1.0;
    for(int i=0;i<4;i++){
      for(int j=0;j<3;j++){
        if(k==0){
          Ud[k][i][j] = 1.0;
          count++;
        }else if (k==1){
          Ud[k][i][j] = 2.0;
          count++;
        }
      }
    }
  }

  Tensor C(2,4,5,1.0);
  Vector3d Cd(2,4,5,1.0);
  for(int k=0;k<2;k++){
    count =1.0;
    for(int i=0;i<4;i++){
      for(int j=0;j<5;j++){
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
      //std::cout << "U:\n" << Ud << std::endl;
      //std::cout << "V:\n" << Vd << std::endl;

      //Cd = all(Cd,0.0);
      //std::cout << "C:\n" << Cd << std::endl;

    //Vector count_U(Ud.rows(),1,"all");
      //count_U = all(count_U,0.0);
      //std::cout << "U_c:\n" << count_U << std::endl;

     // std::fill(count_U[0], count_U[Ud.rows()], 0);
      //std::fill(count_V[0], count_V[Ud.rows()], 0);
  
  Tensor prev_U(2,5,3, 0.0);
  Vector3d prev_Ud(2,4,3, 0.0);
  Vector3d prev_Vd(2,5,3, 0.0);
  double err,miss=0.0;
  for(int k=0;k<1;k++){
      for(int i=0;i<4;i++){
        for(int j=0;j<5;j++){
          err = U[k][i]*U[k][i];
          std::cout << "err:" << err << std::endl;
          miss = 0.0;
          for(int d=0;d<3;d++){
          prev_Ud[k][i][d]+=vector3d_mul(Vd,Vd,Ud,k,d,i,j);
          prev_Vd[k][j][d]+=vector3d_mul(Ud,Ud,Vd,k,d,j,i);
          std::cout << "prev_Ud:" << prev_Ud[k][i][d] << std::endl;
          }

        }
      }
      std::cout << "prev_Ud.cols():\n" << prev_Ud.cols() << std::endl;
      std::cout << "prev_U:\n" << prev_U[k] << std::endl;
      std::cout << "prev_Ud:\n" << prev_Ud[k] << std::endl;
      std::cout << "prev_Vd:\n" << prev_Vd[k] << std::endl;
  }
  
  std::cout << "--------------------------------------------------------------------------" << std::endl;
 /*
  Matrix R(4,5);
  R = {{0,1,2,3,0},
       {1,1,2,3,4},
       {2,3,4,1,4},
       {2,3,4,1,4}};
  
  Matrix X(4*5, 4+5,0.0);
  Matrix prev_X(4*5, 4+5,0.0);
  Vector Y(X.rows(), 0.0, "all");
  Vector prev_Y(X.rows(), 0.0, "all");
  //std::cout << X << "\n" << Y << std::endl; //ok
  int line_num = 0;
  for (int i=0; i < 4; i++){
    for(int j = 0; j < 5; j++){
      if(R[i][j] != 0){
        X[line_num][i] = 1.0;
        X[line_num][4+j] = 1.0;
        Y[line_num] = R[i][j];
      }
      line_num++;
    }
  }
  std::cout << "FM:line_num" << line_num << "\n" << X << "\n" << Y << std::endl;

  double diff = max_norm(prev_X - X);
  std::cout << "diff:" << diff << std::endl;
 */
  return 0;
}
