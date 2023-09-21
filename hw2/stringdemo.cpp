#include <cstring>
#include <iostream>

int main() {
    char mystring[80] = "ComputerScience";
    char yourstring[80];
    char *astring;
    //---------------------------------------

    yourstring = mystring;
    strncpy(astring, mystring, 80);

    astring = mystring;                // make a copy?
    strncpy(yourstring, mystring, 80); // make a copy?
    std::cout << astring << "\n";
    std::cout << yourstring << "\n";

    mystring[0] = '*'; // which one actually made a copy?
    std::cout << astring << "\n";
    std::cout << yourstring << "\n";

    return 0;
}
