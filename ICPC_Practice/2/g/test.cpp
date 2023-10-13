#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long

int main() {
	int x;
	cin >> x;

	int c = 0;
	int arr[10000];
	for (int i = 1; i*i < x; i++) {
		if ((x - i*i) % (2*i) == 0) {
			arr[c++] = ((x - i*i)/(2*i) + i);
		}
	}

	cout << c << endl;
	if (c > 0) { cout << arr[--c]; }
	for (c--; c >= 0; c--) {
		cout << " " << arr[c];
	}
	cout << endl;
}
