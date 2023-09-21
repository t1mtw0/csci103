#include <iostream>
#include <limits.h>
// you may not add more libraries
using namespace std;


int main()
{
	// Input code
	int data[100]; // at most 100 elements
	int n;
	cin >> n;      // get the number of elements to be input and used
	for(int i=0; i < n; i++){
		cin >> data[i];  // get each of the n inputs
	}

	// Task Description: find the MIN of the array data (e.g. 3 in array [5,3,6,7]).
	// Note that limits.h gives INT_MIN and INT_MAX, i.e. int x = INT_MIN; for minimum integer  
	int min;

	// YOUR code goes here - you may introduce (scalar) variables but no more arrays.
    min = data[0];
    for (int i = 1; i < n; ++i) {
        if (data[i] < min) {
            min = data[i];
        }
    }

	// Output Code: Prints resulting MIN  	
	cout << min << endl;

	return 0;
}