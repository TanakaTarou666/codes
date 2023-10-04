#include"../src/matrix.h"
#include <sstream>

int main(){
//
const std::string METHOD_NAME="NMF";

int D;
double beta;
double alpha;
int pata_num = 4;

//読み込み
  Matrix MAEdata(12,5,5.0),tmp_MAEdata(12,5,5.0); // kesson x 5pata-n
  Matrix paraMAE(12,4,0.0); //kesson x 3para
  Matrix AUCdata(12,5,0.0),tmp_AUCdata(12,5,0.0); 
  Matrix paraAUC(12,4,0.0);
  int count;
  int i; //dataのカウント
  int j; //strの4列目を出力するためのカウント
  int kesson_i = 0;
  
  std::string str, tmp;
  std::string date = "data";
  //出力ファイル名
  std::string filenameMAEout = "../../../RESULT/MAE/" + METHOD_NAME+ "_artificialityMAE" + "-" + date + ".txt";
  std::string filenameAUCout = "../../../RESULT/AUC/" + METHOD_NAME+ "_artificialityAUC" + "-" + date + ".txt";

  for(int kesson = 4500 ; kesson <= 7500 ; kesson += 500){ 
    double mae_ave = 0;
    double auc_ave = 0;
  for(int D = 2 ; D <= 9; D++){ //潜在次元数
  for(double beta = 0; beta < 0.5; beta += 0.5){
  for(double alpha = 0; alpha <= 0.002; alpha += 10){
  //入力ファイル名

    std::ostringstream oss;
    std::ostringstream oss2;
    oss << std::setprecision(10) << beta;
    std::string BETA(oss.str());

    oss2 << std::setprecision(10) << alpha;
    std::string ALPHA(oss2.str());

  std::string filenameMAE = "../../../RESULT/" + METHOD_NAME + "-" + date + "/" + METHOD_NAME+ "_artificiality" + std::to_string(kesson) 
                            + "/" + std::to_string(D) + "_" + BETA + "_" + ALPHA + "/" + METHOD_NAME + "MAE.txt";
  std::string filenameAUC = "../../../RESULT/" + METHOD_NAME + "-" + date + "/" + METHOD_NAME+ "_artificiality" + std::to_string(kesson) 
                            + "/" + std::to_string(D) + "_" + BETA + "_" + ALPHA + "/" + METHOD_NAME + "AUC.txt";
  std::ifstream ifs(filenameMAE);
  if (!ifs)
  {
    std::cerr << "ファイルopen失敗: " << filenameMAE << std::endl;
  }
  else
  {
    
    i = 0;
    while(getline(ifs, str)){
      //retention.resize(retention.size() + 1);
      //retention[i].resize(5);
      std::istringstream stream(str); 
      j = 0;
      while(getline(stream, tmp, '\t')){
        if(j == 4){
            //std::cout << tmp << "|" << j << "," << i << "|" << kesson_i << std::endl;
            tmp_MAEdata[kesson_i][i] = std::stod(tmp);
            i++;
        }
        j++;
      }
      if(i == 5) //潜在次元巣6などの倍の行表示対策
          break;
    }
    /*
    count = 0;
    for(int i=0;i<5;i++){
        if(tmp_MAEdata[kesson_i][i] < MAEdata[kesson_i][i])
            count++;
            //std::cout << "count" << i << ":" << tmp_MAEdata[kesson_i][i] << ":" << MAEdata[kesson_i][i] << filenameMAE << std::endl;
    }
    if(count >= 3){
            MAEdata = tmp_MAEdata;
            //std::cout << "count:" << MAEdata << std::endl;
            paraMAE[kesson_i][0] = D;
            paraMAE[kesson_i][1] = beta;
            paraMAE[kesson_i][2] = alpha;
    }
    */
    double tmp_ave = 0.0;
    for(int i=0;i<4;i++){
      tmp_ave+=tmp_MAEdata[kesson_i][i];
    //std::cout << "count" << i << ":" << tmp_MAEdata[kesson_i][i] << ":" << MAEdata[kesson_i][i] << filenameMAE << std::endl;
    }
    if(mae_ave == 0)mae_ave=tmp_ave;
    if(tmp_ave<=mae_ave){
      mae_ave=tmp_ave;
            MAEdata[kesson_i] = tmp_MAEdata[kesson_i];
            std::cout << "ave:" << tmp_ave << std::endl;
            paraMAE[kesson_i][0] = D;
            paraMAE[kesson_i][1] = beta;
            paraMAE[kesson_i][2] = alpha;
            paraMAE[kesson_i][3] = mae_ave / pata_num;
    }
  }//else
  std::cout << "MAE end :" << filenameMAE << std::endl;
  ifs.close();

  //std::cout << "count:" << MAEdata[1] << std::endl;
  

  //AUC maxをとる
  std::ifstream ifs2(filenameAUC);
  if (!ifs2)
  {
    std::cerr << "ファイルopen失敗: " << filenameAUC << std::endl;
  }
  else
  {
    i = 0;
    while(getline(ifs2, str)){
      //retention.resize(retention.size() + 1);
      //retention[i].resize(5);
      std::istringstream stream(str); 
      j = 0;
      while(getline(stream, tmp, '\t')){
        if(j == 4){
            tmp_AUCdata[kesson_i][i] = std::stod(tmp);
            i++;
        }
        j++;
      }
      if(i == 5) //潜在次元巣6などの倍の行表示対策
        break;
    }
    /*
    count = 0;
    for(int i=0;i<5;i++){
        if(tmp_AUCdata[kesson_i][i] <= 1.0){
          if(tmp_AUCdata[kesson_i][i] > AUCdata[kesson_i][i])
              count++;
              //std::cout << "count" << i << ":" << tmp_AUCdata[kesson_i][i] << ":" << AUCdata[kesson_i][i] << filenameAUC << std::endl;
        }else{ //AUC>1.0
          std::cout << "AUC > 1.0 : kesson:" << kesson_i << "para:" << paraAUC[kesson_i] << std::endl;
        }
    }
    if(count >= 3){
            AUCdata[kesson_i] = tmp_AUCdata[kesson_i];
            paraAUC[kesson_i][0] = D;
            paraAUC[kesson_i][1] = beta;
            paraAUC[kesson_i][2] = alpha;
    }
    */
    double tmp_ave = 0.0;
    for(int i=0;i<4;i++){
      tmp_ave+=tmp_AUCdata[kesson_i][i];
    //std::cout << "count" << i << ":" << tmp_MAEdata[kesson_i][i] << ":" << MAEdata[kesson_i][i] << filenameMAE << std::endl;
    }
    if(auc_ave == 0)auc_ave=tmp_ave;
    if(tmp_ave>=auc_ave){
      auc_ave=tmp_ave;
            AUCdata[kesson_i] = tmp_AUCdata[kesson_i];
            std::cout << "ave:" << tmp_ave << std::endl;
            paraAUC[kesson_i][0] = D;
            paraAUC[kesson_i][1] = beta;
            paraAUC[kesson_i][2] = alpha;
            paraAUC[kesson_i][3] = auc_ave / pata_num;
    }
  }//else
  std::cout << "AUC end :" << filenameAUC << std::endl;
  ifs2.close();
  }//alpha
  }//beta
  }//D
  kesson_i++;
  //std::cout << "kesson" << std::endl;
  }//KESSON

    //std::cout << "書き込み" << std::endl;

    //書き込み
    std::ofstream ofs(filenameMAEout, std::ios::out);
    if (!ofs)
    {
      std::cerr << "ファイルopen失敗: " << filenameMAEout << std::endl;
    }
    else
    {   
      for(int kesson_i=0;kesson_i<12;kesson_i++){
        for(int i=0; i < 5; i++){
            ofs << MAEdata[kesson_i][i] << "\t";
        }
            ofs << paraMAE[kesson_i][0] << "\t"
                << paraMAE[kesson_i][1] << "\t"
                << paraMAE[kesson_i][2] << "\t"
                << paraMAE[kesson_i][3] << "\t"
                << std::endl; 
      }
      ofs.close();
    }
    std::cout << "MAE w end" << std::endl;
    //書き込み
    std::ofstream ofs2(filenameAUCout, std::ios::out);
    if (!ofs2)
    {
      std::cerr << "ファイルopen失敗: " << filenameAUCout << std::endl;
    }
    else
    {   
      for(int kesson_i=0;kesson_i<12;kesson_i++){
        for(int i=0; i < 5; i++){
            //AUC, F-measure, AUCの順
            ofs2 << AUCdata[kesson_i][i] << "\t";
        }
            ofs2 << paraAUC[kesson_i][0] << "\t"
                << paraAUC[kesson_i][1] << "\t"
                << paraAUC[kesson_i][2] << "\t"
                << paraAUC[kesson_i][3] << "\t"
                << std::endl;
        //std::cout << kesson_i << std::endl;
      }
      ofs2.close();
    }
    std::cout << "AUC w end" << std::endl;
  return 0;
}