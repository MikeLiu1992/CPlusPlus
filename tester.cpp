#include <stdio.h>
#include <iostream>
#include <vector>
#include "quant_vec.h"


int main() {

  quant_double f1(std::vector<int>{1,2,3});
  quant_double f2(f1);
  double x1[3] = {1,2,3};
  quant_double f3(x1, 3);
  f1.push_back(4);
  f1.push_back(1);
  f1.push_back(2);
  f1.push_back(3);
  for (int i = 0; i < 7; i ++)
        std::cout << f1[i] << ";";
  std::cout << std::endl;
  for (int i = 0; i < 3; i ++)
        std::cout << f2[i] << ";";
  std::cout << std::endl;
  for (int i = 0; i < 3; i ++)
        std::cout << f3[i] << ";";
  std::cout << std::endl;
  
   //Arithmetic Tester
  quant_double f4(f1);
  quant_double f5(f4 + f1);
  for (int i = 0; i < 7; i ++)
        std::cout << f5[i] << ";";
  std::cout << std::endl;
  quant_double f6(f5 - f1);
  for (int i = 0; i < 7; i ++)
        std::cout << f6[i] << ";";
  std::cout << std::endl;
  quant_double f7(f5 * f1);
  for (int i = 0; i < 7; i ++)
        std::cout << f7[i] << ";";
  std::cout << std::endl;
  
  quant_double f8(f5 / f1);
  for (int i = 0; i < 7; i ++)
        std::cout << f8[i] << ";";
  std::cout << std::endl;

  //Assignment Operator:
  quant_double f9 = f8;
  for (int i = 0; i < 7; i ++)
        std::cout << f8[i] << ";";
  std::cout << std::endl;
  return 0;
}