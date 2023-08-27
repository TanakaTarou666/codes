#include"../src/recom.h"

//ユーザ数
const int user_number=return_user_number();
//アイテム数
const int item_number=return_item_number();
//データの名前
const std::string data_name=return_data_name();
//入力するデータの場所
const std::string InputDataName="data/sparse_"+data_name
  +"_"+std::to_string(user_number)
  +"_"+std::to_string(item_number)+".txt";
//クラスタリング手法名
const std::string METHOD_NAME="MF";
  
int main(int argc, char *argv[]){
  if(argc != 5){
	std::cerr << "コマンドライン引数を正しく指定してください\n開始欠損パターン数, 終了欠損パターン数, 開始潜在次元%, 終了潜在次元%\n"
			  << "例: xxx.out 1 5 5.5 12" << std::endl;
	exit(1);
  }

  std::string tmp, str;
  bool noError = true;
  int cin[2];
  double din[2];
  for(int i = 1; i <= argc - 1; i++){
    tmp = argv[i];
    //数値変換が正しくできるか判定
    if(i > 2){
      try{
        std::stod(tmp);
      }catch(...){
        noError = false;
      }
    } else {
      try{
        std::stoi(tmp);
      }catch(...){
        noError = false;
      }
    }
    //0以上か判定
    if(noError){
      if(i > 2){
        if(std::stod(tmp) <= 0.0){
          noError = false;
        }
      } else {
        if(std::stoi(tmp) < 1){
          noError = false;
        }
      }
    }
    //エラー出力
    if(!noError){
      std::cerr << "コマンドライン引数を正しく指定してください" << std::endl;
      exit(1);
    } else {
      if(i > 2){
        din[i - 3] = std::stod(tmp);
      } else {
		    cin[i - 1] = std::stoi(tmp) - 1;
      }
	  }
  }
  if(cin[0] > cin[1]){
    std::cerr << "開始欠損パターン数が終了欠損パターン数を上回っています" << std::endl;
    exit(1);
  }
  if(din[0] > din[1]){
    std::cerr << "開始潜在次元%が終了潜在次元%を上回っています" << std::endl;
    exit(1);
  }

  std::vector<int> firstKESSONSeed_main(0);

  //欠損数ループ
  for(int kesson = KESSON_BEGIN; kesson <= KESSON; kesson += KIZAMI){
    //MFのパラメータでループ
    for(double mf_K = din[0] ; mf_K <= din[1]; mf_K++){
    for(double mf_beta = 0.01; mf_beta <= 0.13; mf_beta += 0.02){
    for(double mf_alpha = 0.001; mf_alpha >= 0.001; mf_alpha /= 10){
      std::vector<double> para = {mf_K, mf_beta, mf_alpha};
      std::vector<std::string> dirs = MkdirMF({METHOD_NAME}, para, kesson);

      //Recomクラスの生成
      Recom recom(user_number, item_number, 0, 0, kesson, cin[0], cin[1]);
      recom.method_name() = METHOD_NAME;
      recom.FIRST_KESSON_SEED() = firstKESSONSeed_main; //main関数のものと同期
      recom.missing() = kesson;

      recom.calculationloadsaveChoicedMaeAuc(dirs[0]); 
      recom.calculationloadsaveSEEDandAverage(dirs[0]);
      recom.calculationloadsaveaverageMaeFmeasureAuc(dirs[0]);   
      // recom.calculationloadsaveAUC(dirs[0]);
      std::cout << mf_K << "% " << mf_beta << " " << mf_alpha << std::endl;
    }}}
  }
	return 0;
}