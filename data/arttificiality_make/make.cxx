#include<random>
#include<iostream>

int main(void){
  const int userNum=10, itemNum=10, clusterNum=10;

  for(int roop= 0 ;roop<2 ; roop++){

    for(int ell=0;ell<userNum;ell++){
        for(int i=0;i<clusterNum;i++){
            for(int k=0;k<itemNum;k++){
                if(i >= 4){
                    std::cout << i%4 + 1 << " ";
                }else{
                    std::cout << i+1 << " ";
                }
            }
        }
        std::cout << std::endl;
    }

    for(int ell=0;ell<userNum;ell++){
        for(int i=0;i<clusterNum;i++){
            for(int k=0;k<itemNum;k++){
                if(i % 4 ==0)
                    std::cout << i % 4 +4 << " ";
                else
                    std::cout << i % 4 << " ";
            }
        }
        std::cout << std::endl;
    }

    for(int ell=0;ell<userNum;ell++){
        for(int i=0;i<clusterNum;i++){
            for(int k=0;k<itemNum;k++){
                if(i==0 || i==1)
                    std::cout << i+3 << " ";
                else if(i >= 6)
                    std::cout << i-5 << " ";
                else
                    std::cout << i-1 << " ";
            }
        }
        std::cout << std::endl;
    }
    for(int ell=0;ell<userNum;ell++){
        for(int i=0;i<clusterNum;i++){
            for(int k=0;k<itemNum;k++){
                if(i >= 7)
                    std::cout << i-6 << " ";
                else if(i >= 3)
                    std::cout << i-2 << " ";
                else
                    std::cout << i+2 << " ";    
            }
        }
        std::cout << std::endl;
    }
    ////////////////////////////////////////////
    }
  return 0;
}
