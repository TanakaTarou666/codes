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
const std::string METHOD_NAME="QFCS";

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
    for(double m=1.01;m<1.03;m+=0.01){
	  for(double lambda=10;lambda<=100;lambda*=10){
	
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
	  //前回のSeedと精度の平均値読み込み
	  if(cin[0] > 0){
		recom.loadSEEDandAverage(dir[0]);
	  }
	  //データ入力
	  recom.input(InputDataName);
	  //aveMAEの初期化
	  //recom.reset_aveMAE();
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


		



		//std::cout<<test.centers()<<std::endl;

	    //目的関数値の計算
	    test.set_objective();
	    //recomに目的関数値を渡す
	    recom.obje(recom.Ccurrent())=test.objective();
	    //recomに帰属度とクラスタ中心を渡す
	    recom.crisp(test.membership());
		//相関係数計算  6/22 add
	    recom.pearsonsim_clustering();
	    //クラスタリング＋ピアソン相関係数の計算
	    //GroupLens Methodで予測
	    recom.reset2();
	    //アクティブユーザと同クラスタに属すユーザのみ計算に使用
		//未評価値予測(ubukata)
		//recom.UbukataForSphericalData(clusters_number);
        //球面化からの復元
        recom.RestoreForSphericalData(SphericalSum);
		//中央値復元
		//recom.restore_median(correction);
	    recom.pearsonpred2_after_clustering();             //←ここでgrouplens
	    //recom.filtering_similarities();
	    //recom.pearsonpred2();
	    recom.mae(dir[0], 0);
	    recom.fmeasure(dir[0], 0);
	    recom.save_roc_for_artificiality(dir[0]);
		recom.auc(dir[0]);
	    recom.ofs_objective(dir[0]);
	    test.ofs_selected_data(dir[0]);
		recom.current() = tmp_current;
	    recom.save_mae_f(dir);
	  	recom.SeedSet2();
	  }
	  recom.precision_summury(dir);
	  recom.choiceMAE_h_art(dirs, m, lambda);
	  recom.choiceAUC_h_art(dirs, m, lambda);
	std::cout << "m = " << m << ", λ = " << lambda << std::endl;
	//recom.total_average_mae(dir);
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
