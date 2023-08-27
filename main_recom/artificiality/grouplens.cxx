#include"../../src/recom.h"

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
const std::string METHOD_NAME="GROUPLENS";

int main(int argc, char *argv[]){
	auto start2=std::chrono::system_clock::now();

  if(argc < 3){
	std::cerr << "開始欠損パターン数, 終了欠損パターン数をコマンドライン引数で指定してください\n"
			  << "例: " << METHOD_NAME << ".out 1 5" << std::endl;
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
	
  std::vector<int> KESSON500Seed_main(0);

  //欠損数ループ
  for(int kesson = KESSON_BEGIN; kesson <= KESSON; kesson += KIZAMI){
    std::vector<std::string> dirs = Mkdir({METHOD_NAME}, kesson); //=Mkdir({"FIREFLY", "GROUPLENS"})

    //Recomクラスの生成
    Recom recom(user_number, item_number, 0, 0, KESSON, cin[0], cin[1]);
    recom.method_name() = METHOD_NAME;
    recom.FIRST_KESSON_SEED() = KESSON500Seed_main;
    //時間計測
    auto start=std::chrono::system_clock::now();
	  //前回のSeedと精度の平均値読み込み
    if(cin[0] > 0){
      recom.loadSEEDandAverage(dirs[0]);
    }
    //データ入力
    recom.input(InputDataName);
    recom.missing() = kesson;
    //欠損のさせ方ループ
	  for(recom.current() = 0; recom.current() + recom.current_start() <= recom.current_end(); recom.current()++){
	    recom.SeedSet1();
      //初めの欠損ループを現在の欠損ループ数に代入(後のファイル出力のため)
      int tmp_current = recom.current();
      recom.current() += recom.current_start();
      //初期化
      recom.reset();
      //データを欠損
      recom.revise_missing_values();
      recom.reset2();
      recom.pearsonsim();
      //GroupLens, 元のコードでは(dirs[1], 1)
      recom.pearsonpred2();
      recom.mae(dirs[0], 0);
      recom.fmeasure(dirs[0], 0);
      recom.save_roc_for_artificiality(dirs[0]);
		  recom.auc(dirs[0]);
	  	recom.current() = tmp_current;
      recom.save_mae_f(dirs);
	  	recom.SeedSet2();
		}
    recom.precision_summury(dirs);
    //recom.total_average_mae(dirs);
    //計測終了
    auto end=std::chrono::system_clock::now();
    auto endstart=end-start;
    std::string time
      =std::to_string
      (std::chrono::duration_cast<std::chrono::hours>(endstart).count())
      +"h"+std::to_string
      (std::chrono::duration_cast<std::chrono::minutes>(endstart).count()%60)
      +"m"+std::to_string
      (std::chrono::duration_cast<std::chrono::seconds>(endstart).count()%60)
      +"s";
    //計測時間でリネーム
    /*
    for(int i=0;i<(int)dir.size();i++)
      rename(dir[i].c_str(), (dir[i]+time).c_str());
    */
    recom.saveSEEDandAverage(dirs[0], time);
	  KESSON500Seed_main = recom.FIRST_KESSON_SEED();
  }//kesson
	auto end2=std::chrono::system_clock::now();
	auto endstart2=end2-start2;
	std::cout << std::to_string
		(std::chrono::duration_cast<std::chrono::hours>(endstart2).count())
		<< "h" << std::to_string
		(std::chrono::duration_cast<std::chrono::minutes>(endstart2).count()%60)
		<< "m" << std::to_string
		(std::chrono::duration_cast<std::chrono::seconds>(endstart2).count()%60)
		<< "s" << std::endl;
  return 0;
}
