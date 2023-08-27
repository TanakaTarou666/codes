#include"../../src/recom.h"
#include"../../src/qfcs.h"

//収束条件
#define MAX_ITE 1000
#define DIFF_FOR_STOP 1.0E-10
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
const std::string METHOD_NAME="QFCS_MF";

int main(int argc, char *argv[]){
	double mf_K_distance = 4.0; //刻み%(+)
	double mf_beta_range[3] = {0.01, 0.16, 0.05}; //開始，終了，刻み(+)
	double mf_alpha_range[3] = {0.001, 0.001, 10}; //開始，終了，刻み(*)
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
    //小さすぎないか判定
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
  std::vector<std::string> dirs = MkdirFCS(METHOD_NAME, kesson);
  
  //クラスタ数でループ
  for(int clusters_number=5;clusters_number<=5;clusters_number+=10){
    //Recomクラスの生成
    Recom recom(user_number, item_number,
		clusters_number, clusters_number, kesson, cin[0], cin[1]);
    recom.method_name()=METHOD_NAME;
	recom.FIRST_KESSON_SEED() = firstKESSONSeed_main;
	//recom.setMAE_h();
	//recom.setAUC_h();
    //for(double sigma=1.0;sigma<=1.0;sigma*=2.5){     //←rbfsigmaの値でループ
    for(double m=1.01;m<1.82;m+=0.2){
	  for(double lambda=10;lambda<=10000;lambda*=10){
	
	  //補正値
	  //for(double correction=1.50;correction<=1.50;correction+=0.01){
	
	  //時間計測
	  auto start=std::chrono::system_clock::now();
	  //ユーザ数×ユーザ数
	  QFCS test(item_number, user_number, 
		clusters_number, m, lambda);
	  std::vector<double> parameter= {lambda, m}; //= {lambda, m, correction}
	  std::vector<std::string> dir
	  = Mkdir(parameter, clusters_number, dirs);
	  //前回のSeed読み込み
	  if(cin[0] > 0){
		recom.loadSEED(dir[0]);
	  }
	  //データ入力
	  recom.input(InputDataName);
	  //aveMAEの初期化
	  //recom.reset_aveMAE();
	  recom.missing() = kesson;
	  //MF: NaN判定用
	  std::vector <std::vector <bool>> mf_nan;
	  mf_nan.resize((size_t)((din[1] - din[0]) / mf_K_distance) + 1);
	  for(int i = 0; i < (int)mf_nan.size(); i++){
	  	mf_nan[i].resize((size_t)((mf_beta_range[1] - mf_beta_range[0]) / mf_beta_range[2]) + 1);
	  }
	  //↑のindexに使う（alphaも変化させる場合は用意）
	  int K_index = 0, beta_index = 0;
	  //MFのパラメータ，ディレクトリに使う
	  std::vector<double> mf_para;
	  //欠損のさせ方ループ
	  for(recom.current() = 0; recom.current() + recom.current_start() <= recom.current_end(); recom.current()++){
	  	recom.SeedSet1();
		//初めの欠損ループを現在の欠損ループ数に代入(後のファイル出力のため)
		int tmp_current = recom.current();
		recom.current() += recom.current_start();
	    //データを欠損前に戻して類似度初期化
	    recom.reset();
	    //データを欠損
	    recom.revise_missing_values();
		//中央値を0に変換
		//recom.change_median_artificiality();
		//欠損データをtestに渡す
		test.copydata(recom.sparseincompletedata());
        //球面化時の総和を保持
        Vector SphericalSum=test.sphericalsum();
        //球面化処理
        test.ForSphericalData();
	    test.reset();
	    //初期クラスタサイズ調整変数の設定
	    test.initialize_clustersize();
	    //初期帰属度の設定
	    test.initialize_membership2();
	    //クラスタリングループ数
	    test.iterates()=0;

		//std::cout<< <<std::endl;

		//std::cout<<test.membership()<<std::endl;
		
		//std::cout<< "data"<<test.data()<<std::endl;
		//std::cout<< "v"<<test.centers()<<std::endl;
        //std::cout<<"d"<<test.dissimilarities()<<std::endl;
		//std::cout<<"a"<<test.clusters_size()<<std::endl;
		//std::cout<<"u"<<test.membership()<<std::endl;

	    while(1){
	      test.revise_centers();
		  //std::cout<< "v"<<test.centers()<<std::endl;
	      test.revise_dissimilarities();      //←カーネル込み
          //std::cout<<"d"<<test.dissimilarities()<<std::endl;
		  test.revise_membership();
          //std::cout<<"u"<<test.membership()<<std::endl;
          test.revise_clusters_size();
          //std::cout<<"a"<<test.clusters_size()<<std::endl;
	      double diff_v
		=max_norm(test.tmp_centers()-test.centers());
	      double diff_u
		=max_norm(test.tmp_membership()-test.membership());
	      double diff_p
		=max_norm(test.tmp_clusters_size()-test.clusters_size());
	      double diff=diff_u+diff_v+diff_p;
	      if(std::isnan(diff)){
		std::cout<<"diff is nan \t"<<m<<"\t"
			 <<lambda<<"\tC:"<<clusters_number<<std::endl;
		test.reset();
		exit(1);
	      }
	      if(diff<DIFF_FOR_STOP)break;
	      if(test.iterates()>=MAX_ITE)break;
	      test.iterates()++;
	    }
		//目的関数値の計算
	    test.set_objective();
	    //recomに目的関数値を渡す
	    recom.obje(recom.Ccurrent())=test.objective();
	    //recomに帰属度とクラスタ中心を渡す
	    recom.crisp(test.membership());
		//相関係数計算  6/22 add
	    recom.pearsonsim_clustering();
        //球面化からの復元
        recom.RestoreForSphericalData(SphericalSum);
		
		//MFのパラメータでループ
		for(double mf_K = din[0] ; mf_K < din[1] + mf_K_distance; mf_K += mf_K_distance){
		for(double mf_beta = mf_beta_range[0]; mf_beta < mf_beta_range[1] + mf_beta_range[2]; mf_beta += mf_beta_range[2]){
		for(double mf_alpha = mf_alpha_range[0]; mf_alpha <= mf_alpha_range[1]; mf_alpha *= mf_alpha_range[2]){
		mf_nan[K_index][beta_index] = false;
		mf_para = {mf_K, mf_beta, mf_alpha};
		dir[0] = MkdirMF_afterClustering(dir, mf_para); //ディレクトリ移動
	    recom.reset2();
		//MF: 潜在次元, 正則化, 学習率, 更新回数上限(指定無いと2000)
		if(recom.mf_pred_after_clustering(dirs[0], mf_K, mf_beta, mf_alpha, 2000) == 1){
			mf_nan[K_index][beta_index] = true;
			std::cout << "MF: NaN detected. (K: " << mf_K << "%, beta = " << mf_beta << "alpha = " << mf_alpha << std::endl;
			break;
		}
	    recom.mae(dir[0], 0);
	    recom.fmeasure(dir[0], 0);
	    recom.save_roc_for_artificiality(dir[0], true);
		recom.auc(dir[0]);
	    recom.ofs_objective(dir[0]);
	    test.ofs_selected_data(dir[0]);
	    // recom.save_mae_f(dir);
		dir = Mkdir(parameter, clusters_number, dirs); //ディレクトリ移動
		// std::cout << "KESSON_pt: " << recom.current() + 1 << ", K: " << mf_K << "%, beta = " << mf_beta << ", alpha = " << mf_alpha << " end." << std::endl;
		} //alpha
		beta_index++;
		} //beta
		beta_index = 0;
		K_index++;
		} //K
		recom.current() = tmp_current;
	  	recom.SeedSet2();
	  	K_index = 0;
	  }
	  //MFのパラメータでループ
	  for(double mf_K = din[0] ; mf_K < din[1] + mf_K_distance; mf_K += mf_K_distance){
	  for(double mf_beta = mf_beta_range[0]; mf_beta < mf_beta_range[1] + mf_beta_range[2]; mf_beta += mf_beta_range[2]){
	  for(double mf_alpha = mf_alpha_range[0]; mf_alpha <= mf_alpha_range[1]; mf_alpha *= mf_alpha_range[2]){
		mf_para = {mf_K, mf_beta, mf_alpha};
		dir[0] = MkdirMF_afterClustering(dir, mf_para); //ディレクトリ移動
		//前回のSeedと精度の平均値読み込み
		if(cin[0] > 0){
			if(recom.loadSEEDandAverage(dir[0]) == 1){ //前の実験でNaNが出ていたら1が返され，そのパラメータはスキップ
				recom.saveSEEDandAverage(dir[0], "skipped", true);
				int K_num;
				if(return_user_number() > return_item_number()){
					K_num = std::round(return_item_number() * mf_K / 100);
				} else {
					K_num = std::round(return_user_number() * mf_K / 100);
				}
				std::cout << "K: " << mf_K << "%(" << K_num << "), beta = " << mf_beta << ", alpha = " << mf_alpha << " is skipped." << std::endl;
				break;
			}
		}
		if(!mf_nan[K_index][beta_index]){
			recom.precision_summury2(dir);
		}
		recom.saveSEEDandAverage(dir[0], "", mf_nan[K_index][beta_index]);
		dir = Mkdir(parameter, clusters_number, dirs); //ディレクトリ移動
	  } //alpha
	  beta_index++;
	  } //beta
	  beta_index = 0;
	  K_index++;
	  } //K
	  K_index = 0;
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
	dir	= Mkdir(parameter, clusters_number, dirs); //ディレクトリ移動
	recom.saveSEED(dir[0], time);
	std::cout << "m = " << m << ", λ = " << lambda << std::endl;
    }//lambda
    }//m
    //}//sigma
	firstKESSONSeed_main = recom.FIRST_KESSON_SEED();
  }//number of clusters
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
