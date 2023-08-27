#include"bfcm.h"

BFCM::BFCM(int dimension,
	   int data_number,
	   int centers_number,
	   double fuzzifierEm): 
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  FuzzifierEm(fuzzifierEm){
}

double &BFCM::fuzzifierEm(void){
  return FuzzifierEm;
}

void BFCM::revise_membership(void){
#ifdef CHECK_CLASS
  std::cout<<"BFCM::revise_membership"<<std::endl;
#endif
  Tmp_Membership=Membership;
  for(int k=0;k<data_number();k++){
    int numZeroDissimilarities=0;
    Vector indexZeroDissimilarities(centers_number(), 0.0, "all");
    for(int i=0;i<centers_number();i++){
      if(Dissimilarities[i][k]==0.0){
	numZeroDissimilarities++;
	indexZeroDissimilarities[i]=1.0;
      }
    }
    if(numZeroDissimilarities!=0){
      for(int i=0;i<centers_number();i++){
	Membership[i][k]=indexZeroDissimilarities[i]
	  /numZeroDissimilarities;
      }
    }
    else{
      for(int i=0;i<centers_number();i++){
	double denominator=0.0;
	for(int j=0;j<centers_number();j++){
	  denominator+=Clusters_size[j]/Clusters_size[i]
	    *pow(Dissimilarities[j][k]/Dissimilarities[i][k],
		 1.0/(1.0-FuzzifierEm));
	}
	Membership[i][k]=1.0/denominator;
      }
    }
  }
  return;
}

void BFCM::revise_centers(void){
#ifdef CHECK_CLASS
  std::cout<<"BFCM::revise_centers"<<std::endl;
#endif
//std::cout<<"BFCM::revise_centers"<<std::endl;
int a;
  Tmp_Centers=Centers;
  //std::cout<< Tmp_Centers<<std::endl;
  for(int i=0;i<centers_number();i++){
    double denominator=0.0;
    Vector numerator(Centers[i].size(),0.0,"all");
    for(int k=0;k<data_number();k++){
      denominator+=pow(Membership[i][k],FuzzifierEm);
      for(int ell=0;ell<Data[k].essencialSize();ell++){
      numerator[Data[k].indexIndex(ell)]
          +=pow(Membership[i][k],FuzzifierEm)*Data[k].elementIndex(ell);
          //std::cout<<"Em:"<<FuzzifierEm<<std::endl;
          //std::cout<<i<<":"<<k<<":"<<ell<<"\t"<<Membership[i][k]<<"\t"<<Data[k].elementIndex(ell)<<std::endl;
          //std::cout<<numerator[Data[k].indexIndex(ell)]<<"\t"<<pow(Membership[i][k],FuzzifierEm)*Data[k].elementIndex(ell)<<std::endl;
          //std::cin >> a;
      }
      /*
      std::cout<<"pow(Membership[i][k],FuzzifierEm):"<<pow(Membership[i][k],FuzzifierEm)<<std::endl;
      std::cout<<"denominator:"<<denominator<<std::endl;
      std::cout<<"data:"<<Data[k]<<std::endl;
      std::cout<<"numerator:"<<numerator<<std::endl;
      std::cin >> a;
      */
    }
    Centers[i]=numerator/denominator;
    //std::cout<<"cluster"<<i<<":\tdenomi:"<<denominator<<"\tnume:"<<numerator<<std::endl;
    //std::cout<<i<<":"<<Centers[i]<<std::endl;
    //std::cin >> a;
  }
  //std::cout<<"Center"<<Centers<<std::endl;
  return;
}

void BFCM::revise_clusters_size(void){
#ifdef CHECK_CLASS
  std::cout<<"BFCM::revise_clusters_size"<<std::endl;
#endif
  Tmp_Clusters_size=Clusters_size;
  Vector Tmp(centers_number());
  for(int i=0;i<centers_number();i++){
    Tmp[i]=0.0;
    for(int k=0;k<data_number();k++)
      Tmp[i]+=pow(Membership[i][k],FuzzifierEm)*Dissimilarities[i][k];
  }
  for(int i=0;i<centers_number();i++){
    double denominator=0.0;
    for(int j=0;j<centers_number();j++)
      denominator+=pow(Tmp[j]/Tmp[i],1.0/FuzzifierEm);
    Clusters_size[i]=1.0/denominator;
  }
  return;
}

void BFCM::set_objective(void){
  Objective=0.0;
  for(int i=0;i<centers_number();i++)
    for(int k=0;k<data_number();k++)
      Objective+=pow(Clusters_size[i],1.0-FuzzifierEm)*
        pow(Membership[i][k],FuzzifierEm)*Dissimilarities[i][k];
  return;
}
