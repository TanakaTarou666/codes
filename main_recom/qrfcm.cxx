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
const std::string METHOD_NAME="QRFCM";

int main(int argc, char *argv[]){
	auto start2=std::chrono::system_clock::now();

  if(argc < 5){
	std::cerr << "コマンドライン引数を指定してください\n開始欠損パターン数, 終了欠損パターン数, 開始クラスタ数, 終了クラスタ数\n"
			  << "例: xxx.out 1 5 2 8" << std::endl;
	exit(1);
  }

  std::string tmp, str;
  bool noError = true;
  int cin[4];
  for(int i = 1; i <= 4; i++){
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
  if(cin[2] > cin[3]){
	std::cerr << "開始クラスタ数が終了クラスタ数を上回っています" << std::endl;
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
    for(double m=1.0001;m<=1.0001;m+=0.0003){
      for(double lambda=1000;lambda<=1000;lambda*=10){

		//時間計測
		auto start=std::chrono::system_clock::now();
		//ユーザ数×ユーザ数
		QRFCM test(user_number, user_number, clusters_number, 1, m, lambda);
		//QRFCM test(user_number, user_number, clusters_number, RBFKERNEL, m, lambda);
		std::vector<double> parameter= {lambda, m};
		std::vector<std::string> dir
		= Mkdir(parameter, clusters_number, dirs);
	    //前回のSeedと精度の平均値読み込み
	    if(cin[0] > 0){
		recom.loadSEEDandAverage(dir[0]);
	    }
		//データ入力
		recom.input(InputDataName);
		//欠損数
	  	recom.missing()=kesson;
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
		//相関係数計算
		recom.pearsonsim();
		//データ(相関係数)をtestに渡す
		test.copy_similarities(recom.similarity());	
		//選んだデータがNanになったときシード値変更のための変数
		int ForBadChoiceData=0, InitCentLoopis10=0;
		//クラスタリングの初期値の与え方ループ
		for(recom.Ccurrent()=0;recom.Ccurrent()
			<CLUSTERINGTRIALS;recom.Ccurrent()++){
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
				recom.pearsonpred2();
				recom.mae(dir[0], 0);
				recom.fmeasure(dir[0], 0);
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
			/*
			//動作確認用
			std::cout << "\nIterates: " << test.iterates()
				<< "\nDissimilarities:\n" << test.dissimilarities()
				<< "\nMemberships:\n" << test.membership()
				<< "\nCenters:\n" << test.centers()
				<< "\nClusterSizes:\n" << test.clusters_size()
				<< std::endl;
			*/
			//目的関数値の計算
			test.set_objective();
			//recomに目的関数値を渡す
			recom.obje(recom.Ccurrent())=test.objective();
			//recomに帰属度を渡してクリスプ化
			recom.crisp(test.membership());
			//クラスタリング＋ピアソン相関係数の計算
			//GroupLens Methodで予測
			recom.reset2();
			//アクティブユーザと同クラスタに属すユーザのみ計算に使用
			recom.pearsonpred2_after_clustering();
			//recom.filtering_similarities();
				//recom.pearsonpred2();
			recom.mae(dir[0], 0);
			recom.fmeasure(dir[0], 0);
			recom.roc(dir[0]);
			recom.auc(dir[0]);
			recom.ofs_objective(dir[0]);
			test.ofs_selected_data(dir[0]);
			InitCentLoopis10=0;
			}
		}//initilal setting for clustering
		recom.current() = tmp_current;
		recom.choice_mae_f(dir);
	  	recom.SeedSet2();
		}
		//AUC，MAE，F-measureの平均を計算，出力
		recom.precision_summury(dir);
		std::cout << "m = " << m << ", λ = " << lambda << std::endl;
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
		recom.saveSEEDandAverage(dir[0], time);
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
