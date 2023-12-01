#include "bigint.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
   if (argc != 2) {
      std::cout << "Usage: fib N\nwhere N is an integer >= 2" << std::endl;
      return 1;
   }   
   int N = atoi(argv[1]);
   
   BigInt x("1");
   std::cout << x.to_string() << std::endl;
   BigInt y("1");
   std::cout << y.to_string() << std::endl;
   for (int i=3; i<=N; i++) {
      BigInt tmp = y;
      y.add(x);
      std::cout << y.to_string() << std::endl;
      x = tmp;
   }
}
