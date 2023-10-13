#include <bits/stdc++.h>
#include <cmath>
using namespace std;

#define ll long long
#define ull unsigned long long

void solve() {
	ll l, r, k;
	cin >> l >> r >> k;

	ll sum = 0;
	ll s = (int)(sqrt(k));
	for (ll d = 1; d <= s; d++) {
		if (k % d != 0) continue;
		ll n = k / d;
		if (d != 1 && n % d == 0 || n * d != k) continue;

		int a = (r*d/n - l + d-l%d)/d;
		if (a > 0) sum += a;
	}
	cout << sum << endl;
}

int main(/* int argc, char* argv[] */) {
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		solve();
	}
}
