#include <iostream>
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

	// Task Description: Find the longest run of consecutive, equal values in an array, 
	// outputting the size of the run. (e.g. 1 in [5,3,6,7], 2 in [1,4,2,2]).  
	int maxrun; // store length of the maximum run

	// YOUR code goes here - you may introduce (scalar) variables but no more arrays.
	maxrun = 1;
	int curMaxrun = 1;
	int curValue = data[0];
	for (int i = 1; i < n; ++i) {
		if (curValue == data[i]) {
			curMaxrun++;
		} else {
			maxrun = curMaxrun;
			curMaxrun = 0;
		}
	}

	// Output Code: Prints resulting maximum run 	
	cout << maxrun << endl;

	return 0;
}
