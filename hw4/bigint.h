#ifndef BIGINT_H
#define BIGINT_H
#include <string>
#include <vector>

// Note: it is bad practice to have `using namespaces std;` in
//       a header file.  So where we use C++ objects (cout, cin)
//       and C++ class types (string, vector<int>), you should
//       precede them with `std::`.

// In the .cpp implementation file, it is fine to have a
//  `using namespace std;` statement. So you can put that in the
//  .cpp file and then avoid having to precede everything with `std::`

class BigInt {
  public:
    BigInt(std::string s);         // convert string to BigInt
    std::string to_string() const; // get string representation
    void add(BigInt b);            // add another BigInt to this one
  private:
    // whatever you need
    std::vector<int> digits;
};

#endif