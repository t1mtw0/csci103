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

	// Task Description: reverse array data (e.g. [7,6,3,5] for array [5,3,6,7]).  

	// YOUR code goes here - you may introduce (scalar) variables but no more arrays.
    for (int i = 0; i < n / 2; ++i) {
        int temp = data[n - i];
		data[n - i] = data[i];
		data[i] = temp;
    }

	// Output Code: Prints data after reversal 
	for(int i=0; i < n; i++){
		cout << data[i] << " ";
	}
	cout << endl;

	return 0;
}	