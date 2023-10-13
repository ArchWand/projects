#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long

int f(int n) {
	int sum = 0;
	for (; n > 0; n /= 10) {
		int a = n % 10;
		sum += a*a;
	}
	return sum;
}

int solve(int n, int arr[]) {
	if (arr[n]) return arr[n];
	return arr[n] = min(n, solve(f(n), arr));
}

int main() {
	int arr[1000005];
	for (int i = 0; i < 1000005; arr[i++] = 0);
	arr[1] = 1;
	arr[4] = 4;

	int a, b;
	cin >> a >> b;
	b++;

	int sum = 0;
	for (int i = a; i < b; i++) {
		sum += solve(i, arr);
	}

	cout << sum << endl;
}
