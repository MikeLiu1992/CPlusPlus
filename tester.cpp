#include <stdio.h>
#include <iostream>
#include "quant_vec.h"


int main() {

  /* Initialize the two argument vectors */
  //__m256 evens = _mm256_set_ps(2.0, 4.0, 6.0, 8.0, 11.0, 12.0, 14.0, 17.0);
  //__m256 odds = _mm256_set_ps(1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0);

  /* Compute the difference between the two vectors */
  //__m256 result = _mm256_sub_ps(evens, odds);

  /* Display the elements of the result vector */

  quant_vector<char> f1({'a', 'b', 'c'});
  f1.push_back('d');
  for (int i = 0; i < 4; i ++)
    std::cout << f1[i] << ";";
  std::cout << std::endl << f1.capacity() << std::endl;
  return 0;
}