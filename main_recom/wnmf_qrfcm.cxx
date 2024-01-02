#include"../src/recom.h"
#include"../src/qrfcm.h"

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
const std::string METHOD_NAME="QRFCM_WNMF";

int main(int argc, char *argv[]){
	double mf_K_distance = 1.0; //刻み(+)
	double mf_beta_range[3] = {0.01, 0.13, 0.04}; //開始，終了，刻み(+)
	double mf_alpha_range[3] = {0.001, 0.001, 10}; //開始，終了，刻み(*)
	auto start2=std::chrono::system_clock::now();

  bool noError = true;
  int cin[4];
  double din[6];
  std::string tmp, str;
  if(argc != 11){
	noError = false;
  }
  if(noError){
	for(int i = 1; i <= argc - 1; i++){
		tmp = argv[i];
		//数値変換が正しくできるか判定
		if(i > 4){
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
			if(i > 4){
				if(i > 8){ //m
					if(std::stod(tmp) <= 1.0){
						noError = false;
					}
				} else {
					if(std::stod(tmp) <= 0.0){
						noError = false;
					}
				}
			} else {
				if(std::stoi(tmp) < 1){
				noError = false;
				}
			}
		}
		if(noError){
			if(i > 4){
			din[i - 5] = std::stod(tmp);
			} else {
				cin[i - 1] = std::stoi(tmp) - 1;
			}
		} else {
			break;
		}
	}
  }
  //エラー出力
  if(!noError){
	  std::cerr << "コマンドライン引数を正しく指定してください\n"
				<< "開始欠損パターン数, 終了欠損パターン数, 開始クラスタ数, 終了クラスタ数, 開始潜在次元%, 終了潜在次元%, 開始λ, 終了λ, 開始m, 終了m\n"
				<< "例: xxx.out 1 5 2 8 5.5 12 1 1000 1.0001 1.0007" << std::endl;
	exit(1);
  }
  if(cin[0] > cin[1]){
	std::cerr << "開始欠損パターン数が終了欠損パターン数を上回っています" << std::endl;
	exit(1);
  }
  if(cin[2] > cin[3]){
	std::cerr << "開始クラスタ数が終了クラスタ数を上回っています" << std::endl;
	exit(1);
  }
  if(din[0] > din[1]){
    std::cerr << "開始潜在次元%が終了潜在次元%を上回っています" << std::endl;
    exit(1);
  }
  if(din[2] > din[3]){
    std::cerr << "開始λが終了λを上回っています" << std::endl;
    exit(1);
  }
  if(din[4] > din[5]){
    std::cerr << "開始mが終了mを上回っています" << std::endl;
    exit(1);
  }

  std::vector<int> firstKESSONSeed_main(0);

  //欠損数ループ
  for(int kesson = KESSON_BEGIN; kesson <= KESSON; kesson += KIZAMI){
  std::vector<std::string> dirs = MkdirFCS(METHOD_NAME, kesson);

  //クラスタ数でループ
  for(int clusters_number=cin[2]+1;clusters_number<=cin[3]+1;clusters_number+=1){
    //Recomクラスの生成
    Recom recom(user_number, item_number,
		clusters_number, clusters_number, kesson, cin[0], cin[1]);
    recom.method_name()=METHOD_NAME;
	recom.FIRST_KESSON_SEED() = firstKESSONSeed_main;

	for (double m : {1.001, 1.1, 1.5, 2.3}) {
		for (double lambda : {1000}) {
		//時間計測
		auto start=std::chrono::system_clock::now();
		//ユーザ数×ユーザ数
		QRFCM test(user_number, user_number, clusters_number, 1, m, lambda);
		//QRFCM test(user_number, user_number, clusters_number, RBFKERNEL, m, lambda);
		std::vector<double> parameter= {lambda, m};
		std::vector<std::string> dir
		= Mkdir(parameter, clusters_number, dirs);
		//前回のSeed読み込み
		if(cin[0] > 0){
			recom.loadSEED(dir[0]);
		}
		//データ入力
		recom.input(InputDataName);
	  	recom.missing()=kesson;
		//MF: NaN判定用
		std::vector <std::vector <bool>> mf_nan;
		//↑のindexに使う（alphaも変化させる場合は用意）
		int K_index = 0, beta_index = 0;
		//MFのパラメータ，ディレクトリに使う
		std::vector<double> mf_para;
		mf_nan.resize((size_t)((din[1] - din[0]) / mf_K_distance) + 1);
		for(int i = 0; i < (int)mf_nan.size(); i++){
			mf_nan[i].resize((size_t)((mf_beta_range[1] - mf_beta_range[0]) / mf_beta_range[2]) + 1);
		}
		//クラスタリングの最小目的関数値と，そのときのrecomのMem, Ccurent保持用
		double min_object_clustering = DBL_MAX;
		Matrix tmp_membership(clusters_number, user_number);
		int tmp_Ccurrent = -1;
		//欠損のさせ方ループ
		for(recom.current() = 0; recom.current() + recom.current_start() <= recom.current_end(); recom.current()++){
		std::cout << "Missing pattern: " << recom.current() + recom.current_start() << std::endl;
		recom.SeedSet1();
		//初めの欠損ループを現在の欠損ループ数に代入(後のファイル出力のため)
		int tmp_current = recom.current();
		recom.current() += recom.current_start();
		//データを欠損前に戻して類似度初期化
		recom.reset();
		//データを欠損
		recom.revise_missing_values_new();
		//相関係数計算
		recom.pearsonsim();
		//データ(相関係数)をtestに渡す
		test.copy_similarities(recom.similarity());	
		//選んだデータがNanになったときシード値変更のための変数
		int ForBadChoiceData=0, InitCentLoopis10=0;
		//クラスタリング+GLの結果から初期値を決定するための変数
		int clusteringInitialIndex;
		std::string clusteringMethod = METHOD_NAME;
		clusteringInitialIndex = recom.returnBestClusteringInitial(clusteringMethod.erase(clusteringMethod.find("_")), kesson, parameter, clusters_number, recom.current());
		if(clusteringInitialIndex == -1){
			std::cout << "Correct clustering data is not found.\nClustering will be done by all initials." << std::endl;
		}
		//Objeリセット処理
		for(int i = 0; i < CLUSTERINGTRIALS; i++){
			recom.obje(i) = DBL_MAX;
		}
		//クラスタリングの初期値の与え方ループ
		for(recom.Ccurrent()=0;recom.Ccurrent()
			<CLUSTERINGTRIALS;recom.Ccurrent()++){
				//クラスタリング+GLの正しいデータが存在するか
				if(clusteringInitialIndex != -1 && clusteringInitialIndex != recom.Ccurrent()){
					continue;
				}
				std::cout<<"initial setting for clustering:"
					<<recom.Ccurrent()<<std::endl;
				test.reset();
				//初期クラスタサイズ調整変数の設定
				test.initialize_clustersize();
				//初期クラスタ中心の設定
				test.centersInitializePlusPlus(recom.Ccurrent()
							+ForBadChoiceData);
				/*
				//動作確認用
				std::cout << "Initial Similarities:\n" << recom.similarity() << std::endl;
				std::cout << "Initial Centers:\n" << test.centers() << std::endl;
				std::cout << "Initial ClusterSizes:\n" << test.clusters_size() << std::endl;
				*/
				//クラスタリングループ数
				test.iterates()=0;
				//nanが出た時の回避で使う
				int p=1;
				while(1){
					if(InitCentLoopis10>9){
						test.reset();
						recom.obje(recom.Ccurrent())=DBL_MAX;
						recom.pearsonpred2(); //どうせ採用しないので時間かからないGLのまま
						recom.mae(dir[0], 0, true);
						recom.fmeasure(dir[0], 0, true);
						recom.roc(dir[0]);
						recom.ofs_objective(dir[0]);
						test.ofs_selected_data(dir[0]);
						InitCentLoopis10=0;
						p=0;
						break;
					}
					test.revise_dissimilarities();
					test.revise_membership();
					test.revise_centers();
					test.revise_clusters_size();
					double diff_v
						=max_norm(test.tmp_centers()-test.centers());
					double diff_u
						=max_norm(test.tmp_membership()-test.membership());
					double diff_p
						=max_norm(test.tmp_clusters_size()-test.clusters_size());
					double diff=diff_u+diff_v+diff_p;
					if(std::isnan(diff)){
						std::cout<<"diff is nan"<<std::endl;
						test.reset();
						recom.Ccurrent()--;p=0;
						ForBadChoiceData++;
						InitCentLoopis10++;
						break;
					}
					if(diff<DIFF_FOR_STOP)break;
					if(test.iterates()>=MAX_ITE)break;
					test.iterates()++;
				}
				if(p){
					//目的関数値の計算
					test.set_objective();
					//recomに目的関数値を渡す
					recom.obje(recom.Ccurrent())=test.objective();
					//前回と比べて最小の目的関数値ならmembership保持
					if(test.objective() < min_object_clustering){
						min_object_clustering = test.objective();
						tmp_membership = test.membership();
						tmp_Ccurrent = recom.Ccurrent();
					}
				}
			}//initilal setting for clustering
			// std::cout << "MIN_OBJECT_INDEX = " << tmp_Ccurrent << "\nOBJECT: " << std::fixed << std::setprecision(10)	 << recom.obje() << std::endl;
			//recomに帰属度を渡してクリスプ化
			recom.crisp(tmp_membership);
			//アクティブユーザと同クラスタに属すユーザのみ計算に使用
			recom.reset2();
			recom.Ccurrent() = tmp_Ccurrent;
			
			//MFのパラメータでループ
			for(double mf_K = din[0] ; mf_K < din[1] + mf_K_distance; mf_K += mf_K_distance){
				double mf_beta=0;
				double mf_alpha=0;
				mf_nan[K_index][beta_index] = false;
				mf_para = {mf_K, mf_beta, mf_alpha};
				dir[0] = MkdirMF_afterClustering(dir, mf_para); //ディレクトリ移動
				recom.reset2();
				//MF: 潜在次元, 正則化, 学習率, 更新回数上限(指定無いと2000)
				if(recom.wnmf_pred_after_clustering(dir[0], mf_K, 2000) == 1){
					mf_nan[K_index][beta_index] = true;
					std::cout << "MF: NaN detected. (K: " << mf_K << "%, beta = " << mf_beta << ", alpha = " << mf_alpha << ")" << std::endl;
		  			dir = Mkdir(parameter, clusters_number, dirs); //ディレクトリ移動
					continue;
				}
				recom.mae(dir[0], 0, true);
				recom.fmeasure(dir[0], 0, true);
				recom.roc(dir[0]);
				recom.auc(dir[0]);
				recom.ofs_objective(dir[0]);
				test.ofs_selected_data(dir[0]);
				InitCentLoopis10=0;
				dir = Mkdir(parameter, clusters_number, dirs); //ディレクトリ移動
				// std::cout << "KESSON_pt: " << recom.current() + 1 << ", K: " << mf_K << "%, beta = " << mf_beta << ", alpha = " << mf_alpha << " end." << std::endl;
			beta_index++;
			beta_index = 0;
			K_index++;
			} //K
		K_index = 0;
		recom.current() = tmp_current;
		//MFのパラメータでループ
		double mf_alpha=0;
		double mf_beta =0;
		for(double mf_K = din[0] ; mf_K < din[1] + mf_K_distance; mf_K += mf_K_distance){
			mf_para = {mf_K, mf_beta, mf_alpha};
			dir[0] = MkdirMF_afterClustering(dir, mf_para); //ディレクトリ移動
			if(!mf_nan[K_index][beta_index]){
				recom.choice_mae_f(dir, 2);
			}
			dir = Mkdir(parameter, clusters_number, dirs); //ディレクトリ移動
		beta_index++;
	    beta_index = 0;
		K_index++;
		} //K
		K_index = 0;
	  	recom.SeedSet2();
		min_object_clustering = DBL_MAX;
		} //欠損パターン
		//MFのパラメータでループ
		double mf_alpha=0;
		double mf_beta =0;
		for(double mf_K = din[0] ; mf_K < din[1] + mf_K_distance; mf_K += mf_K_distance){
			mf_para = {mf_K, mf_beta, mf_alpha};
			dir[0] = MkdirMF_afterClustering(dir, mf_para); //ディレクトリ移動
			//前回のSeedと精度の平均値読み込み
			if(cin[0] > 0){
				if(recom.loadSEEDandAverage(dir[0]) == 1){ //前の実験でNaNが出ていたら1が返され，そのパラメータはスキップ
					recom.saveSEEDandAverage(dir[0], "skipped", true);
					std::cout << "K: " << mf_K << "%, beta = " << mf_beta << ", alpha = " << mf_alpha << " is skipped." << std::endl;
					dir = Mkdir(parameter, clusters_number, dirs); //ディレクトリ移動
					continue;
				}
			}
			try{
				if(!mf_nan[K_index][beta_index]){
					recom.precision_summury2(dir);
				}
			}catch(std::invalid_argument){
				std::cout << "invalid_argument: K_index=" << K_index << ", beta_index=" << beta_index
						<< ", mf_nan:\n";
				for(int indexK = 0; indexK < (int)mf_nan.size(); indexK++){
					for(int indexB = 0; indexB < (int)mf_nan[indexK].size(); indexB++){
						std::cout << mf_nan[indexK][indexB] << ", ";
					}
					std::cout << "\n";
				}
				std::cout << " |true=" << true << std::endl;
			}
			recom.saveSEEDandAverage(dir[0], "", mf_nan[K_index][beta_index]);
			dir = Mkdir(parameter, clusters_number, dirs); //ディレクトリ移動
		beta_index++;
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
		recom.saveClusterInfo(dir[0]);
		std::cout << "m = " << m << ", λ = " << lambda << std::endl;
      }//lambda
    }//m
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
