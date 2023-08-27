#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <Eigen/Sparse>
using namespace Eigen;

//sed -e "s/::/ /g" ratings.dat > ratings_rowmajor.dat
//を実行後
const std::string data_file = "combined_data_";

constexpr int SIZE = 100480507; //100480507

int main(void){
  //評価値
  VectorXd ItemElem = VectorXd::Zero(SIZE);
  //アイテムの番号
  VectorXd ItemIndex = VectorXd::Zero(SIZE);
  //ユーザの番号
  VectorXd UserIndex = VectorXd::Zero(SIZE);
  //各ユーザが評価したアイテム数
  VectorXd UserIndexSize = VectorXd::Zero(SIZE);
  //各アイテムを評価したユーザ数
  VectorXd ItemIndexSize = VectorXd::Zero(SIZE);
  int index = 0;
  //ユーザ番号，アイテム番号，評価値，
  int uid = -1, iid = -1;
  int rate;
  std::string tmp;
  for(int files = 1; files <= 4; files++){
    //データ読み込み
    std::ifstream ifs(data_file + std::to_string(files) + ".txt");
    if(ifs.fail()){
      std::cerr<<"file error"<<std::endl;
      exit(1);
    }
    while(std::getline(ifs, tmp)){
      if(tmp.find(":") == std::string::npos){
        std::stringstream ss{tmp};
        std::string str;
        std::getline(ss, str, ',');
        uid = std::stoi(str) - 1;
        std::getline(ss, str, ',');
        rate = std::stoi(str);
        //ユーザサイズ計算
        UserIndexSize(uid)++;
        //アイテムサイズ計算
        ItemIndexSize(iid)++;
        //データ入力
        ItemElem(index)=rate;
        ItemIndex(index)=iid;
        UserIndex(index)=uid;
        index++;
      } else {
        tmp.erase(tmp.find(":"));
        iid = std::stoi(tmp) - 1;
      }
    }
    ifs.close();
  }
  // for(int i=0;i<SIZE;i++){
  //   ifs >> uid >> iid >> rate ;
  //   //ユーザサイズ計算
  //   UserIndexSize(uid-1)++;
  //   //アイテムサイズ計算
  //   ItemIndexSize(iid-1)++;
  //   //データ入力
  //   ItemElem(i)=rate;
  //   ItemIndex(i)=iid-1;
  //   UserIndex(i)=uid-1;
  // }
  //欠番を詰める
  std::ofstream ofs1("ユーザ欠番.txt");
  std::ofstream ofs2("映画欠番.txt");
  std::map<int, int> RealUserIndex, RealItemIndex;
  int ROW=0,COL=0;
  for(int i=0;i<SIZE;i++){
    if(UserIndexSize(i)>0){
      RealUserIndex.insert(std::make_pair(i, ROW));
      ROW++;
    }
    else
      if(2649429>i) //2649429
	ofs1<<i<<std::endl;
    if(ItemIndexSize(i)>0){
      RealItemIndex.insert(std::make_pair(i, COL));
      //std::cout<<COL<<" "<<i<<std::endl;
      COL++;
    }
    else
      if(17770>i) //17770
	ofs2<<i<<std::endl;
  }
  std::cout<<ROW<<" "<<COL<<std::endl;
  //出力
  std::ofstream ofs("ratings_colmajor.txt");
  int sum=0;
  for(int i=0;i<SIZE;i++){
    for(int sz=0;sz<ItemIndexSize(i);sz++)
      ofs<<RealItemIndex.at(i)
	     <<" "<<RealUserIndex.at(UserIndex(sum+sz))
	     <<" "<<ItemElem(sum+sz)<<std::endl;
    sum+=ItemIndexSize(i);
  }
  return 0;
}