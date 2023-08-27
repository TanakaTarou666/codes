#include <array>
#include <boost/generator_iterator.hpp>
#include <boost/random.hpp>
#include <boost/random/binomial_distribution.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

template<class T, std::size_t N>
inline T sum(std::array<T, N>& ar)
{
  T s = 0;
  for(T& e : ar) s += e;
  return s;
}

template<std::size_t N>
std::array<int, N> multinomial(int n, std::array<double, N>& pvals)
{
  static boost::mt19937 rng( static_cast<unsigned int>(time(0)) );
  //boost::mt19937 rng;
  std::array<int, N> sample;
  sample.fill(0);
  try
    {
      if(sum(pvals) - pvals.at(N-1) > 1.0)
        {
          throw "summation of pvals[:-1] >= 1.0";
        }
      double remp = 1.0;
      int rem = n, idx = 0;
      for(double& pval : pvals)
        {
          double p = pval / remp;
          boost::binomial_distribution<> binom(rem, p);
          boost::variate_generator<boost::mt19937&, boost::binomial_distribution<> > bpdf(rng, binom);
          int hit = bpdf();
          if(hit > 0)
            {
              sample.at(idx) = hit;
            }
          rem -= hit;
          remp -= pval;
          idx += 1;
        }
    } 
  catch(std::string errmsg)
    {
      std::cerr << errmsg << std::endl;
      exit(1);
    }
  return sample;
}

int main(void){
//多項分布f(x1,...,xk;n;p1,...,pk)
  std::array<double, 3> vals;//k=3;
  //p1=0.1, p2=0.2, p3=0.7
  vals[0]=0.8;
  vals[1]=0.1;
  vals[2]=0.1;
  int data_number1 = 50;
  int data_number2 = 50;
  int data_number3 = 50;
  int data_number4 = 50;
  //resultにfを代入
  for(int i=0;i<data_number1;i++){
  std::array<int, 3> result=multinomial(100, vals);
  std::cout << result[0] << "\t"
            << result[1] << "\t"
            << result[2] << std::endl;
  }

  vals[0]=0.1;
  vals[1]=0.8;
  vals[2]=0.1;
  //resultにfを代入
  for(int i=0;i<data_number3;i++){
  std::array<int, 3> result=multinomial(100, vals);
  std::cout << result[0] << "\t"
            << result[1] << "\t"
            << result[2] << std::endl;
  }
  
  vals[0]=0.1;
  vals[1]=0.1;
  vals[2]=0.8;
  //resultにfを代入
  for(int i=0;i<data_number3;i++){
  std::array<int, 3> result=multinomial(100, vals);
  std::cout << result[0] << "\t"
            << result[1] << "\t"
            << result[2] << std::endl;
  }
  
  vals[0]=0.33;
  vals[1]=0.33;
  vals[2]=0.33;
  //resultにfを代入
  for(int i=0;i<data_number3;i++){
  std::array<int, 3> result=multinomial(100, vals);
  std::cout << result[0] << "\t"
            << result[1] << "\t"
            << result[2] << std::endl;
  }

  return 0;
}
