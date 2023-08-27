#include"qrfcm.h"

QRFCM::QRFCM(int dimension,
	     int data_number,
	     int centers_number,
	     double rbfsigma,
	     double fuzzifierEm,
	     double fuzzifierLambda): 
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  RFCM(dimension, data_number, centers_number, rbfsigma),
  QFCM(dimension, data_number, centers_number,
       fuzzifierEm, fuzzifierLambda){
}

void QRFCM::revise_centers(void){
#ifdef CHECK_CLASS
  std::cout<<"QRFCM::revise_centers"<<std::endl;
#endif
  Tmp_Centers=Centers;
  for(int i=0;i<centers_number();i++){
    double denominator=0.0;
    Vector numerator(Centers[i].size(), 0.0, "all");
    Vector numerator2(Centers[i].size(), 0.0, "all");
    for(int k=0;k<data_number();k++){
      denominator+=pow(Membership[i][k],FuzzifierEm);
      numerator+=pow(Membership[i][k],FuzzifierEm)*UnitMatrixData[k];
      //numerator2[k]=pow(Membership[i][k],FuzzifierEm);
      //std::cout << k<< UnitMatrixData[k] << std::endl;  
    }                      
    //std::cout << i << "\t"<< numerator[i] << "\t"<< numerator2[i]<< std::endl;                               
    Centers[i]=numerator/denominator;
    //std::cout <<"Centers" <<i <<":"<< Centers[i] << std::endl;
  }
  return;
}

void QRFCM::set_objective(void){
  Objective=0.0;
  double tmp=0.0;
  for(int i=0;i<centers_number();i++){
    double numerator=0.0,denominator=0.0;
    for(int k1=0;k1<data_number();k1++){
      denominator+=pow(Membership[i][k1],FuzzifierEm);
      tmp+=pow(Clusters_size[i],1.0-FuzzifierEm)
	*pow(Membership[i][k1],FuzzifierEm);
      for(int k2=0;k2<data_number();k2++)
	numerator+=pow(Membership[i][k1],FuzzifierEm)
	  *pow(Membership[i][k2],FuzzifierEm)
	  *Kernel[k1][k2];
    }
    Objective+=pow(Clusters_size[i],1.0-FuzzifierEm)
      *numerator/(2.0*denominator);
  }
  Objective+=1.0/(FuzzifierLambda*(FuzzifierEm-1.0))*(tmp-1.0);
  return;
}

void QRFCM::revise_dissimilarities(void){
  //std::cout << "QRFCM::revise_dissimilarities" << std::endl;
  bool negativeFlag=false;
  for(int i=0;i<centers_number();i++){
    Vector w=Kernel*Centers[i];
    double y=Centers[i]*w;
    //std::cout << "w:\n" << w << "\ny = " << y << std::endl;
    for(int k=0;k<data_number();k++){
      Dissimilarities[i][k] = Kernel[k][k] - 2.0 * w[k] + y;
      //std::cout << "negativeFlagValue: " << 1 - FuzzifierLambda * (1.0 - FuzzifierEm) * Dissimilarities[i][k] << std::endl;
      if(1 - FuzzifierLambda * (1.0 - FuzzifierEm) * Dissimilarities[i][k] < 0.0){
        negativeFlag = true;
      }
    }
  }
  if(negativeFlag){
    double tmp_beta = 0.0, beta = 0.0;
    //Matrix CentersT=transpose(Centers);
    for(int i=0;i<centers_number();i++){
      double CentersInnerproduct = Centers[i]*Centers[i];
      for(int k=0;k<data_number();k++){
	      //std::cout<<"i="<<i<<" k="<<k<<std::endl;
	      tmp_beta = -2.0 * (1 - FuzzifierLambda * (1.0 - FuzzifierEm) * Dissimilarities[i][k]) /
                  (FuzzifierEm - 1.0) * FuzzifierLambda * (1.0 - 2.0 * Centers[i][k] + CentersInnerproduct);
        if(beta < tmp_beta)
          beta = tmp_beta;
      }
    }
    for(int i=0;i<centers_number();i++){
      double CentersInnerproduct=Centers[i]*Centers[i];
      for(int k=0;k<data_number();k++){
	double tmp1 = (beta / 2.0) * (1.0 - 2.0 * Centers[i][k] + CentersInnerproduct);
	//std::cout<<"Centers[i][k]="<<Centers[i][k]<<std::endl;
	//std::cout<<"tmp1="<<tmp1<<std::endl;
	Dissimilarities[i][k] += tmp1;
	//std::cout<<"Dissimilarities[i][k]="
	//<<Dissimilarities[i][k]<<std::endl;
	//std::cout<<std::endl;
      }
    }
  }//if(negativeFlag)
  return;
}
