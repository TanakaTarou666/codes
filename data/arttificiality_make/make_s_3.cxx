#include<random>
#include<iostream>

int main(void){
  const int userNum=2, itemNum=15, clusterNum=4;
  int count=0;

    for(int ell=0;ell<userNum;ell++){
        count=0;
        std::cout << itemNum*clusterNum << " ";
        for(int i=0;i<clusterNum;i++){
            for(int k=0;k<itemNum;k++){
                std::cout << count <<" "<< i+1 << " ";
                count++;
            }
        }
        std::cout << std::endl;
    }

    for(int ell=0;ell<userNum;ell++){
        count=0;
        std::cout << itemNum*clusterNum << " ";
        for(int i=0;i<clusterNum;i++){
            for(int k=0;k<itemNum;k++){
                std::cout << count <<" ";
                if(i==0)
                    std::cout << i+4 << " ";
                else
                    std::cout << i << " ";
                count++;
            }
        }
        std::cout << std::endl;
    }

    for(int ell=0;ell<userNum;ell++){
        count=0;
        std::cout << itemNum*clusterNum << " ";
        for(int i=0;i<clusterNum;i++){
            for(int k=0;k<itemNum;k++){
                std::cout << count <<" ";
                if(i==0 || i==1)
                    std::cout << i+3 << " ";
                else
                    std::cout << i-1 << " ";
                count++;
            }
        }
        std::cout << std::endl;
    }

    for(int ell=0;ell<userNum;ell++){
        count=0;
        std::cout << itemNum*clusterNum << " ";
        for(int i=0;i<clusterNum;i++){
            for(int k=0;k<itemNum;k++){
                std::cout << count <<" ";
                if(i==clusterNum-1)
                    std::cout << 1 << " ";
                else
                    std::cout << i+2 << " ";
                count++;
            }
        }
        std::cout << std::endl;
    }
  return 0;
}
