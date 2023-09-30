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
const std::string METHOD_NAME="WNMF";

int main(int argc, char *argv[]){
	auto start2=std::chrono::system_clock::now();

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

	
  std::vector<int> firstKESSONSeed_main(0); //recomクラスのものをmain関数で保持する用
  //欠損数ループ
  for(int kesson = KESSON_BEGIN; kesson <= KESSON; kesson += KIZAMI){
  //MFのパラメータでループ
  for(double mf_K = din[0] ; mf_K <= din[1]; mf_K++){
    std::vector<double> para = {mf_K, 0, 0};
    std::vector<std::string> dirs = MkdirMF({METHOD_NAME}, para, kesson);

  //Recomクラスの生成
  Recom recom(user_number, item_number, 0, 0, kesson, cin[0], cin[1]);
  recom.method_name() = METHOD_NAME;
  recom.FIRST_KESSON_SEED() = firstKESSONSeed_main; //main関数のものと同期

  //前回のSeedと精度の平均値読み込み
  if(cin[0] > 0){
    if(recom.loadSEEDandAverage(dirs[0]) == 1){ //前の実験でNaNが出ていたら1が返され，そのパラメータはスキップ
      recom.saveSEEDandAverage(dirs[0], "skipped", true);
      int K_num;
      if(return_user_number() > return_item_number()){
        K_num = std::round(return_item_number() * mf_K / 100);
      } else {
        K_num = std::round(return_user_number() * mf_K / 100);
      }
      std::cout << "K: " << mf_K << "%(" << K_num << " is skipped." << std::endl;
      break;
    }
  }
  //時間計測
  auto start=std::chrono::system_clock::now();
  //データ入力
  recom.input(InputDataName);
  recom.missing() = kesson;
  //NaN判定用
  bool mf_nan = false;
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
    //動作確認用
    //std::cout << "Initial Similarities:\n" << recom.similarity() << std::endl;
    //MF: 潜在次元, 正則化, 学習率, 更新回数上限(指定無いと2000)
    if(recom.wnmf_pred(dirs[0], mf_K, 4000) == 1){
      mf_nan = true;
      break;
    }
    recom.mae(dirs[0], 0);
    recom.fmeasure(dirs[0], 0);
    recom.roc(dirs[0]);
		recom.current() = tmp_current;
		recom.choice_mae_f(dirs, 0);
    recom.SeedSet2();
		}
  if(!mf_nan){
    //AUC，MAE，F-measureの平均を計算，出力
    recom.precision_summury(dirs);
  }
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
  recom.saveSEEDandAverage(dirs[0], time, mf_nan);
  firstKESSONSeed_main = recom.FIRST_KESSON_SEED();
  std::cout << "K = " << mf_K <<  " is done." << std::endl;
  // if(!mf_nan)
  }//mf_K
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
