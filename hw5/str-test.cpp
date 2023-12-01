#include <iostream>
#include <iomanip>
#include "str.h"

int main()
{
  Str sblank;
  const Str sref("World");
  Str s0("!");
  Str s1("Small");
  Str s1_copy(s1);
  
  std::cout << "sblank=" << sblank << std::endl;
  std::cout << "s1=" << s1 << std::endl;
  std::cout << "s1_copy=" << s1_copy << std::endl;

  std::cout << s1 + sref + s0 << std::endl;
  std::cout << s1 + " world" + s0 << std::endl;

  s1 += sref;
  s1 += "!";

  std::cout << s1 << std::endl;
  
  s0 = s1 = sref;
  std::cout << "s0 and s1 should be equal to \"World\". Actual values: " << s0 << " " << s1 << std::endl;
  s0 = s1 = "hello world";
  std::cout << "s0 and s1 should be equal to \"hello world\". Actual values: " << s0 << " " << s1 << std::endl;

  std::cout << s1 << " has size " << s1.size() << std::endl;

  s1[0] = 'H';
  s1[6] = 'W';

  std::cout << s1 << std::endl;

  std::cout << "The first letter of sref is " << sref[0] << std::endl;

  s1 = "Hello";
  Str s2("He");
  Str s3("Jello");
  std::cout << "Is " << s1 << " == " << s2 << "? " << std::boolalpha << (s1 == s2) << std::endl;
  std::cout << "Is " << s1 << " != " << s2 << "? " << std::boolalpha << (s1 != s2) << std::endl;
  std::cout << "Is " << s1 << " != " << s1 << "? " << std::boolalpha << (s1 != s1) << std::endl;
  std::cout << "Is " << s1 << " < " << s2 << "? " << std::boolalpha << (s1 < s2) << std::endl;
  std::cout << "Is " << s1 << " < " << s3 << "? " << std::boolalpha << (s1 < s3) << std::endl;
  std::cout << "Is " << s1 << " > " << s2 << "? " << std::boolalpha << (s1 > s2) << std::endl;
  std::cout << "Is " << s1 << " > " << s3 << "? " << std::boolalpha << (s1 > s3) << std::endl;

  std::cout << "Enter a string: " << std::endl;
  std::cin >> s1;
  std::cout << "You entered: " << s1 << std::endl;

  return 0;
}

