#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long

int main(/* int argc, char* argv[] */) {
	int r, c, k;
	cin >> r >> c >> k;

	int arr[r];
	for (int i = 0; i < r; arr[i++] = 0);
	for (int i = 0; i < c; i++) {
		int n;
		cin >> n;
		arr[--n]++;
	}

	sort(arr, arr+r, greater<int>());

	int sum = 0;
	for (int i = 0; i < k && i < r; i++) {
		sum += arr[i];
	}

	cout << sum << endl;
}
