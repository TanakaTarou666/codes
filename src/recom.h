#include"sparseMatrix.h"
#include"matrix.h"
#include"vector3d.h"
#include <numbers>
#include<map>
#include<filesystem>
//欠損のさせ方を何通りにするか
 //#define MISSINGTRIALS 4
//クラスタリングの初期値を何通りにするか
#define CLUSTERINGTRIALS 1//4//1
//#define CLUSTERINGTRIALS 1
//pearson, eicf, co-clustering
#define METHOD_NUMBER 2
//BookCrossingは10240欠損させる
//他は20480欠損させる
//BEGINは最初の欠損数，ENDは最大の欠損数
#ifdef BOOK
#define KESSON 20000
#define KESSON_BEGIN 20000
#define KIZAMI 5000
#elif defined SUSHI
#define KESSON 40000
#define KESSON_BEGIN 40000
#define KIZAMI 50000
#elif defined SUSHI_NINE
#define KESSON 25000
#define KESSON_BEGIN 25000
#define KIZAMI 5000
#elif defined SUSHI_450I_7U
#define KESSON 15000
#define KESSON_BEGIN 15000
#define KIZAMI 5000
#elif defined ARTIFICIALITY // uekara 7500 500 500
//#define KESSON 5
//#define KESSON_BEGIN 5
#define KESSON 7400//500//2
#define KESSON_BEGIN 6500//52
#define KIZAMI 100
#elif defined JESTER
#define KESSON 100000
#define KESSON_BEGIN 100000
#define KIZAMI 80000
#elif defined EPINIONS_TWENTY
#define KESSON 70000
#define KESSON_BEGIN 70000
#define KIZAMI 10000
#elif defined EPINIONS_20I_20U
#define KESSON 95000
#define KESSON_BEGIN 95000
#define KIZAMI 10000
#elif defined EPINIONS_18I_18U //131726
#define KESSON 100000
#define KESSON_BEGIN 100000
#define KIZAMI 10000
#elif defined EPINIONS_15
#define KESSON 100000
#define KESSON_BEGIN 100000
#define KIZAMI 10000
#elif defined NETFLIX
#define KESSON 50000
#define KESSON_BEGIN 50000
#define KIZAMI 10000
#elif defined MOVIE100K
#define KESSON 40000
#define KESSON_BEGIN 40000
#define KIZAMI 30000
#elif defined SAMPLE
#define KESSON 1
#define KESSON_BEGIN 1
#define KIZAMI 5
#else
#define KESSON 20000
#define KESSON_BEGIN 20000
#define KIZAMI 10000
#endif

#ifndef __RECOM__
#define __RECOM__

class Recom{
protected:
  std::string METHOD_NAME_recom;
  //欠損のさせ方を決めるシード値
  int SEED;
  //欠損のさせ方ループ数，クラスタリング初期値ループ数，現在の欠損数，一番初めは何ループ目かの数（cinで入力）, 何ループ目までやるか
  int Current, CCurrent, Missing, Current_start, Current_end;
  //欠損後データ
  SparseMatrix SparseIncompleteData;
  //欠損前データ
  SparseMatrix SparseCorrectData;
  //球面正規データ
  SparseMatrix NormalizedData;
  //欠損させた箇所，類似度
  Matrix KessonIndex, Similarity;
  //行帰属度，列帰属度
  Matrix Mem, ItemMem;
  //評価値の平均値
  Vector aveData;
  //MAE, F-measure, AUC
  Matrix resultMAE, resultFmeasure;
  Matrix choiceMAE, choiceFmeasure, choiceAUC;
  double aveMAE;
  //予測評価値
  Vector Prediction;
  //欠損させた箇所のスパースデータの列番号
  Vector SparseIndex;
  //Recall，Fallout
  Vector TP_FN, FP_TN;
  //目的関数値
  Vector Obje;
  //w of EICF
  Vector W;
  //最高MAEの保存
  double aveMAE_h;
  //最高AUCの保存
  double aveAUC_h;
  //同じパターン数の欠損数500のSEED
  std::vector<int> firstKESSONSeed;
  //前の実験のSEED
  int prevExpSeed;
  //平均値
  Vector Averages;
  //最適な初期値
  Matrix bestObj;
  //データを読んだ欠損パターン数
  //（loadSEEDandAverageでNaNが出なかった初期値の数を数えるのに使う）
  int loadedPattern;
 public:
  //ユーザ数，アイテム数，行クラスタ数，列クラスタ数，最大欠損数
  Recom(int user,
        int item,
	int user_cen,
	int item_cen,
	int miss,
  int cin_start,
  int cin_end);
  std::string &method_name(void);
  Vector obje(void) const;
  Matrix kessonindex(void) const;
  Matrix similarity(void) const;
  double similarity(int, int);
  double &obje(int index);
  int &current(void);//欠損のさせ方番号
  int &current_start(void);//一番初めは何ループ目かの数（cinで入力）
  int &current_end(void);//おわりは何ループ目かの数（cinで入力）
  int &Ccurrent(void);//クラスタリングの初期値番号
  int &missing(void); //現在の欠損数
  std::vector<int> &FIRST_KESSON_SEED(void);
  void input(std::string);
  //Seedを設定
  void SeedSet1(void);
  void SeedSet2(void);
  //初期化
  void reset(void);
  void reset2(void);
  void reset_aveMAE(void);
  //評価値データの中央値を0に変換
  void change_median(void);
  void change_median_artificiality(void);
  //評価値データから平均値を差し引き保持
  void change_aveData(void);
  //データを欠損
  void revise_missing_values_new(void);
  void revise_missing_values(void);
  //MAEの計算，textに保存
  void mae(std::string, int, bool mfcl = false); //MF+クラスタリングの場合:mfcl = true
  //F-measureの計算，textに保存，indexはROC用ループ添字
  void fmeasure(std::string, int, bool mfcl = false);
  //ROCで必要な値をtextに保存
  void roc(std::string);
  //ROCの横軸の値で小さい順にソート
  void Sort(Vector &fal, Vector &tru, int index);
  //AUCの計算，textに保存
  void auc(std::string);
  //Seedとか保存
  void ofs_objective(std::string);
  //選ばれたクラスタリング初期値によるMAE,Fmeasureの欠損させ方数平均
  int min_objective_index(void);
  void choice_mae_f(std::vector<std::string>, int p=1);
  //maeとfmeasure出力:人工データ用
  void save_roc_for_artificiality(std::string dir, bool mfcl = false); //MF+クラスタリングの場合:mfcl = true
  void save_mae_f(std::vector<std::string>);
  void out_mae_f(std::vector<std::string>);
  //予測結果をtextに保存
  void save_prediction(std::string);
  //AUCの計算，text1に読み込むROCファイル，text2に平均AUCを保存
  void precision_summury(std::vector<std::string>);
  void precision_summury2(std::vector<std::string>); //MF+クラスタリング用(MAE・F-measureをファイルからロード，ROCのtxtは初期値1パターンのみ作られchoiceフォルダは存在しない)
  //人工データ用：総平均MAEの計算と出力
  void total_average_mae(std::vector<std::string>);
  //クラスタリングのみで予測値計算
  void revise_prediction(void);
  //Efficient Incremental Collaborative Filtering system
  void computation_w(void);
  void revise_prediction2(const Matrix &V);
  //ピアソン相関係数計算
  void pearsonsim(void);
  //行クラスタでフィルタにかけた状態で相関係数計算
  void pearsonsim_clustering(void);
  //PCM用類似度計算
  void pearsonsim_for_pcm(const Matrix &Membership,
			  const Vector &Threshold);
  //予測値計算:FireFly
  void pearsonpred1(void);
  //予測値計算:GroupLens
  void pearsonpred2(void);
  void pearsonpred2_after_clustering(void);
  //予測値計算:MF
  int mf_pred(std::string dir, double K, double beta, double alpha = 1.0E-2, int steps = 2000);
  int mf_pred_after_clustering(std::string dir, double K, double beta, double alpha = 1.0E-2, int steps = 2000);
  //予測値計算:NMF
  int nmf_pred(std::string dir, double K,int steps = 2000);
  int nmf_pred_after_clustering(std::string dir, double K, int steps = 2000);
  //予測値計算:QFCMF
  int qfcmf_pred(std::string dir, double K, int steps=2000, int C=2,double Lambda=100, double FuzzifierEm=1.01, double beta = 0.05, double alpha = 1.0E-2);
  //予測値計算:QFCNMF
  int qfcnmf_pred(std::string dir, double K, int steps = 2000, int C=2,double Lambda=100, double FuzzifierEm=1.01);
  //予測値計算:MPBMF
  int mpbmf_pred(std::string dir, int K, int Scale, double D, double beta, double alpha = 1.0E-2, int steps = 2000);
  //予測値計算:FM
  int fm_pred(std::string dir, double K, double beta, double alpha = 1.0E-2, int steps = 2000);
  //予測値計算:Ubukata
  void Ubukata(int clusters_number);
  //予測値計算:Ubukata(球面データ用)
  void UbukataForSphericalData(int clusters_number);
  //予測値計算:Ubukata
  void Ubukata_CentersSim(int clusters_number);
  //予測値計算:Ubukata(球面データ用)
  void UbukataForSphericalData_CentersSim(int clusters_number);
  //球面化からの復元
  void RestoreForSphericalData(const Vector &Sum);
  //
  void restore_aveData(void);
  //中央値復元
  void restore_median(double correction);
  //正規化からの復元
  void RestoreForMMMData(const Vector &Sum);
  //RFCM用
  void filtering_similarities(void);
  //indexのユーザの既評価値平均を計算
  double user_average(int index);
  SparseMatrix sparsecorrectdata(void) const;
  SparseVector &sparsecorrectdata(int index);
  SparseMatrix sparseincompletedata(void) const;
  SparseVector &sparseincompletedata(const int &index);
  //収束した帰属度をクリスプ化
  void crisp(const Matrix &Membership);
  //recomに帰属度とクラスタ中心を渡す
  void copy_mem_cen(const Matrix &Membership, const Matrix &ItemMembership);
  //最高MAEの保存
  void setMAE_h(void);
  void choiceMAE_h_art(std::vector<std::string> dir, double m, double lam);
  void choiceMAE_h(void);
  //最高AUCの保存
  void setAUC_h(void);
  void choiceAUC_h_art(std::vector<std::string> dir, double m, double lam);
  void choiceAUC_h(void);
  //SEED値と平均の読み込み
  int loadSEEDandAverage(std::string dir);
  void loadSEED(std::string dir);
  //SEED値と平均の保存
  void saveSEEDandAverage(std::string dir, std::string time, bool nan = false);
  void saveSEED(std::string dir, std::string time);
  //AUC再計算用
  double choicedAuc_recalculation(int i, std::string dir);
  void calculationloadsaveChoicedMaeAuc(std::string dir);
  double averageAuc_recalculation(std::string dir);
  void calculationloadsaveSEEDandAverage(std::string dir);
  void calculationloadsaveaverageMaeFmeasureAuc(std::string dir);
  double Auc_recalculation(int i, int j, std::string dir);
  void calculationloadsaveAUC(std::string dir);
  int returnBestClusteringInitial(std::string method, int kesson, std::vector<double> parameter, int centerNum, int current);
  //各クラスタ情報の出力
  void saveClusterInfo(std::string dir);
};
//ユーザ数を返す
int return_user_number(void);
//アイテム数を返す
int return_item_number(void);
//設定した閾値を返す
double return_threshold(void);
//最大評価値を返す
double return_max_value(void);
//中央値を返す
double return_median(void);
//データの名前を返す
std::string return_data_name(void);
//textを改行する
void FILE_ENDL(std::string text);
//何通りかの初期値を与えた場合，目的関数最大時のROCのを選ぶ
void Rename(std::string filename, std::string newname);
std::vector<std::string> MkdirFCCM(std::string);
std::vector<std::string> MkdirFCS(std::string, int);
std::vector<std::string> MkdirUBUKATA(std::string);
std::vector<std::string>
Mkdir(std::vector<double> para, int c, std::vector<std::string> dirs);
std::vector<std::string>
Mkdir(std::vector<std::string> methods, int kesson);
std::vector<std::string>
MkdirMF(std::vector<std::string> methods, std::vector<double> para, int kesson);
std::string MkdirMF_afterClustering(std::vector<std::string> dir, std::vector<double> para);
const std::vector<std::string> FCCM = {"PEAR", "CO"};
const std::vector<std::string> FCS = {"PEAR"};
const std::vector<std::string> UBUKATA = {"UBUKATA"};

#endif
