#include <bits/stdc++.h>
#include <cmath>
using namespace std;

#define ll long long
#define ull unsigned long long

int main(/* int argc, char* argv[] */) {
	ull n;
	cin >> n;

	ull j = ceill(sqrtl(n));
	if (n > j*j - j) {
		cout << 2*j-1 << endl;
	} else {
		cout << 2*j-2 << endl;
	}
}

