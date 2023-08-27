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
const std::string METHOD_NAME="QRFCM";
  
int main(int argc, char *argv[]){
  if(argc < 3){
	std::cerr << "コマンドライン引数を指定してください\n開始欠損パターン数, 終了欠損パターン数\n"
			  << "例: xxx.out 1 5" << std::endl;
	exit(1);
  }

  std::string tmp, str;
  bool noError = true;
  int cin[2];
  for(int i = 1; i <= 2; i++){
    tmp = argv[i];
    //数字以外が入っていないか判定
    for(int j = 0; j < (int)tmp.length(); j++){
      if(!std::isdigit(tmp[j])){
        noError = false;
        break;
      }
    }
    //int型の最大値を超えてないか判定
    if(noError){
      try{
        std::stoi(tmp);
      }catch(std::out_of_range&){
        noError = false;
      }
    }
    //1以上か判定
    if(noError){
      if(std::stoi(tmp) < 1){
        noError = false;
      }
    }
    //エラー出力
    if(!noError){
      std::cerr << "コマンドライン引数は" << 1 << " から " << INT_MAX << " の範囲で指定してください" << std::endl;
      exit(1);
    } else {
		cin[i - 1] = std::stoi(tmp) - 1;
	}
  }
  if(cin[0] > cin[1]){
	std::cerr << "開始欠損パターン数が終了欠損パターン数を上回っています" << std::endl;
	exit(1);
  }

  std::vector<int> firstKESSONSeed_main(0);

  //欠損数ループ
  for(int kesson = KESSON_BEGIN; kesson <= KESSON; kesson += KIZAMI){
  std::vector<std::string> dirs = MkdirFCS(METHOD_NAME, kesson);

  //クラスタ数でループ
  for(int clusters_number=2;clusters_number<=8;clusters_number+=1){
    //Recomクラスの生成
    Recom recom(user_number, item_number,
		clusters_number, clusters_number, kesson, cin[0], cin[1]);
    //欠損数
	  	recom.missing()=kesson;
    recom.method_name()=METHOD_NAME;
	recom.FIRST_KESSON_SEED() = firstKESSONSeed_main;
    for(double m=1.0001;m<1.0008;m+=0.0003){
      for(double lambda=1.0;lambda<=1000;lambda*=10){
		std::vector<double> parameter= {lambda, m};
		std::vector<std::string> dir
		= Mkdir(parameter, clusters_number, dirs);

		recom.calculationloadsaveChoicedMaeAuc(dir[0]); 
    recom.calculationloadsaveSEEDandAverage(dir[0]);
    recom.calculationloadsaveaverageMaeFmeasureAuc(dir[0]);   
		recom.calculationloadsaveAUC(dir[0]);
    std::cout << m <<" " << lambda<<" "<<clusters_number<<  std::endl;
		}
	 }
	}
  }
	return 0;
}