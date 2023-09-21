#include <iostream>
// you may not add more libraries
using namespace std;

int main()
{
	// Input code
	int data[100]; // at most 100 elements
	int n;
	cin >> n;      // get the number of elements to be input and used
	for(int i = 0; i < n; i++){
		cin >> data[i];  // get each of the n inputs
	}

	// Task Description: find the SUM of the array data (e.g. 6 for [1,2,3]).  
	int sum;

	// YOUR code goes here - you may introduce (scalar) variables but no more arrays.
	for (int i = 0; i < n; ++i) {
		sum += data[i];
	}

	// Output Code: Prints resulting SUM 	
	cout << sum << endl;

	return 0;
}
