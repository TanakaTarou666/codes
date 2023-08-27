#include<iostream>
#include<fstream>

int main(void){
  std::string filename = "sparse_jester_2916_140.txt";
  std::ifstream ifs(filename);
  if(!ifs){
    std::cerr << "File can't open." << std::endl;
    exit(1);
  }
  std::string tmp;
  int sum = 0, line = 1;
  
  while(std::getline(ifs, tmp)){
    if(tmp.size() == 0){
      std::cerr << "tmp.size() == 0 is true.\ntmp = \"" << tmp
                << "\", tmp.size() = " << tmp.size()
                << ", line = " << line 
                << "\nsum = " << sum << std::endl;
      exit(1);
    }
    tmp.erase(tmp.find(" "), tmp.length() - tmp.find(" "));
    sum += std::stoi(tmp);
    line++;
  }

  std::cout << "Elements: " << sum << " (" << filename << ")" << std::endl;
  return 0;
}
