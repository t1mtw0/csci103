#include "bigint.h"
#include <iostream>

int main() {
   BigInt myInt("103");
   std::cout << myInt.to_string() << std::endl;

   BigInt a("13");
   BigInt b("42");
   b.add(a);    // increase b by a
   std::cout << b.to_string() << std::endl; // prints 55
   b.add(a);    // increase b by a
   std::cout << b.to_string() << std::endl; // prints 68
   
   BigInt c("1");
   BigInt d("9999");
   c.add(d);
   std::cout << c.to_string() << std::endl;
   return 0;
}
