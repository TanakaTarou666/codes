#include"../src/matrix.h"
#include <sstream>

int main(){
//
const std::string METHOD_NAME="MF";

int D;
double beta;
double alpha;
int pata_num = 4;

//読み込み

  int count;
  int i; //dataのカウント
  int j; //strの4列目を出力するためのカウント
  int kesson_i = 0;

  string filename[9] = {"MF","NMF","FM","QRFCM+MF","QRFCM+NMF","QFCMF","QFCNMF"};
  double hensuu[9] = {3,4,3,5,5,6,4};

  Matrix MAEdata(9,7,0.0); 
  Matrix paraMAE(12,4,0.0); 
  
  std::string str, tmp;

  std::string date = "data";
  //出力ファイル名
  std::string filenameMAEout = "../../../RESULT/MAE/MAEmatome-" + date + ".txt";

  for(int name = 0; name < 9 ; name+= 1){
  for(int kesson = 0 ; kesson <= 7 ; kesson += 1){ 

  //入力ファイル名

  std::string filenameMAE = "../../../RESULT/MAE/" + METHOD_NAME+ "_artificialityMAE" + "-" + date + ".txt";

  std::ifstream ifs(filenameMAE);
  if (!ifs)
  {
    std::cerr << "ファイルopen失敗: " << filenameMAE << std::endl;
  }
  else
  {
    
    i = 0;
    while(getline(ifs, str)){
      std::istringstream stream(str); 
      while(getline(stream, tmp, '\t')){
        if(i == 4.0+hensuu[name]){ //num=変数の数
            MAEdata[name][kesson] = std::stod(tmp);
            break;
        }
        i++;
      }
    }
    std::cout << "ex:\n" << MAEdata << std::endl;
  }//else
  ifs.close();

  }//KESSON
  }//name

    //書き込み
    std::ofstream ofs(filenameMAEout, std::ios::out);
    if (!ofs)
    {
      std::cerr << "ファイルopen失敗: " << filenameMAEout << std::endl;
    }
    else
    {   
      for(int name=0;name<9;name++){
        for(int i=0; i < 7; i++){
            ofs << MAEdata[name][i] << "\t";
        }
            ofs << std::endl; 
      }
      ofs.close();
    }

  return 0;
}