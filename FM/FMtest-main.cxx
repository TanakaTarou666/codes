#include"../src/matrix.h"
#include"../src/matrix.h"

int main(){
      int K = 3;
      Matrix X(25, 10,0.0);
      Vector Y(X.rows(), 0.0, "all");
      Matrix V(K,X.cols());

      int line_num;
      for (int i=0; i < 5; i++){
      for(int j = 0; j < 5; j++){
      X[line_num][i] = 1.0;//
      X[line_num][5+j] = 1.0;//
      //std::cout << i+1 << " " << i << ":" << X[line_num][i] << " " << 5+j << ":" << X[line_num][5+j] << std::endl;
      line_num++;
      }
    }

     V = {{0.363705,0.787761,0.158121,0.432216,0.268406,0.260643,0.825071,0.595871,0.431434,0.682668},
      {0.135,0.0665437,0.124959,0.114106,0.57664,0.941527,0.0570628,0.4042,0.527303,0.089849},
      {0.92168,0.612376,0.979481,0.894522,0.77165,0.213524,0.562141,0.693945,0.731995,0.725184}};
    //std::cout << "FM v: "<< V << std::endl;

    double error = 0.0;
    double err = 0.0;\
    double omomi = 1 / X.cols();
    Vector w(X.cols(),omomi,"all");
    bool ParameterNaN = false;
    Vector sum(K,0,"all");
    Vector squareSum(K,0,"all");
    double prediction = 0.0 , linearTerm, w_0 = 1.0;
    w = {1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5,2.7,2.9};
	
  for(int line = 0; line < X.rows(); line++){
        //for(int j = 0; j < SparseIncompleteData[i].essencialSize(); j++){
            prediction = 0.0;
            linearTerm = 0.0;
            // 線形項の計算
            for (int i = 0; i < X.cols(); i++) {
                linearTerm += w[i] * X[line][i];
            }
            //std::cout << "FM: linearTerm end : " << step << std::endl;

            // 交互作用項の計算
            for (int factor = 0; factor < K; factor++) {
                sum[factor] = 0.0;
                squareSum[factor] = 0.0;
                for (int i = 0; i < X.cols(); i++) {
                    sum[factor] += V[factor][i] * X[line][i];
                    squareSum[factor] += V[factor][i] * V[factor][i] * X[line][i] * X[line][i];
                }
                //interactionTerms[factor] = 0.5 * (sum * sum - squareSum);
                prediction += 0.5 * (sum[factor] * sum[factor] - squareSum[factor]);
            }
            std::cout << "t1[" << line << "]=" << prediction << ";" << std::endl;

            // 予測値と誤差の計算
            prediction += linearTerm;
            prediction += w_0;
            Y[line] = prediction;
  }
  //std::cout << "FM: prediction end : " << Y << std::endl;
  //sparseにファイル出力
  int userNum=5, itemNum=5;
  int count=0;
  int line = 0;


    for(int i=0;i<userNum;i++){
      //std::cout << itemNum << " ";
        for(int k=0;k<itemNum;k++){
            //std::cout << k << " " << Y[line] << " " ;
            std::cout << "t[" << line << "]=" << Y[line] << ";" << std::endl;
            line++;
        }
      std::cout << std::endl;
    }

  return 0;
}
