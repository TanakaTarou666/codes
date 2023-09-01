#include<random>
#include<iostream>

int main(void){
  const int userNum=5, itemNum=30, clusterNum=4;
  int count=0;

  for(int roop= 0 ;roop<4 ; roop++){
    for(int ell=0;ell<userNum;ell++){
        count=0;
        std::cout << itemNum*clusterNum-20 << " ";
        for(int i=0;i<clusterNum;i++){
            for(int k=0;k<itemNum;k++){
                if(i == 3 && k == 10){
                break;
                }
                if(i >= 4){
                    std::cout << count << " " << i%4 + 1 << " ";
                }else{
                    std::cout << count << " " << i+1 << " ";
                }
                count++;
            }
        }
        std::cout << std::endl;
    }

    for(int ell=0;ell<userNum;ell++){
        count=0;
        std::cout << itemNum*clusterNum-20 << " ";
        for(int i=0;i<clusterNum;i++){
            for(int k=0;k<itemNum;k++){
                if(i == 3 && k == 10){
                break;
                }
                std::cout << count <<" ";
                if(i % 4 ==0)
                    std::cout << i % 4 +4 << " ";
                else
                    std::cout << i % 4 << " ";
                count++;
            }
        }
        std::cout << std::endl;
    }

    for(int ell=0;ell<userNum;ell++){
        count=0;
        std::cout << itemNum*clusterNum-20 << " ";
        for(int i=0;i<clusterNum;i++){
            for(int k=0;k<itemNum;k++){
                if(i == 3 && k == 10){
                break;
                }
                std::cout << count <<" ";
                if(i==0 || i==1)
                    std::cout << i+3 << " ";
                else if(i >= 6)
                    std::cout << i-5 << " ";
                else
                    std::cout << i-1 << " ";
                count++;
            }
        }
        std::cout << std::endl;
    }

    for(int ell=0;ell<userNum;ell++){
        count=0;
        std::cout << itemNum*clusterNum-20 << " ";
        for(int i=0;i<clusterNum;i++){
            for(int k=0;k<itemNum;k++){
                if(i == 3 && k == 10){
                break;
                }
                std::cout << count <<" ";
                if(i >= 7)
                    std::cout << i-6 << " ";
                else if(i >= 3)
                    std::cout << i-2 << " ";
                else
                    std::cout << i+2 << " ";
                count++;
            }
        }
        std::cout << std::endl;
    }
    ///////////////////////////////////////////
    }
  return 0;
}
