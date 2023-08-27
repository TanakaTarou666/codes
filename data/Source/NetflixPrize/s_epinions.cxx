#include<iostream>
#include<cstdlib>
#include<cmath>
#include<fstream>
#include<iomanip>
#include<cstring>
#include<vector>
#define REP(i,n) for(int i=(0);i<(n);i++)
using namespace std;
int main(const int argc, const char *argv[]){
  std::string argv0=argv[1];
  const int row=atoi(argv[2]); //要素数
  const int newrow=atoi(argv[3]); //ユーザー数
  int size=0, p_row=-1, j=0;
  std::ifstream ifs(argv0);
  if(!ifs){
    cout<<"could not file"<<endl;
    exit(1);
  }
  vector< vector<double> > A;
  A.resize(row);
  for( int i=0; i<row; i++ ){
    A[i].resize(3);
  }
    int tmp=0;
    REP(i,row){
      REP(j,3){
	ifs>>tmp;
	A[i][j]=tmp;
      }
    }

  ofstream ofs_new_sparse("sparse_"+argv0);
  vector<int> c;
  c.resize(newrow);
  REP(i,newrow){
    c[j]=0;
  }

  j=-1;

  REP(i,row){
      if(A[i][0]!=p_row){
        j++;
      } 
      c[j]++;
      p_row = A[i][0];
    }

  j=0;

  REP(i,newrow){
    ofs_new_sparse<<c[j];
    REP(k,c[j]){
      k += size;
     ofs_new_sparse<<" "<<A[k][1]<<" " <<A[k][2];
      k -=size;
    }
    size += c[j];
    ofs_new_sparse<<endl;
    j++;
  }
    return 0;
}
