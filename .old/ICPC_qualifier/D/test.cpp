#include <iostream>
#include <fstream>
using namespace std;

void swap(int arr[], int m) {
	int tmp = arr[m];
	arr[m] = arr[m-1];
	arr[m-1] = tmp;
}

int main(int /* argc */, char* /* argv */[]) {
	int n, m;
	int rows;
	cin >> n >> rows;

	int out[n];
	for (int i = 0; i < n; ++i) {
		out[i] = i+1;
	}

	for (int i = 0; i < rows; ++i) {
		cin >> m;
		swap(out, m);
	}

	// Print `out`, one element on each line
	for (int i = 0; i < n; ++i) {
		cout << out[i] << endl;
	}

	return 0;
}
