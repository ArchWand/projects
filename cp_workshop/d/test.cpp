#include <bits/stdc++.h>
using namespace std;

int main(/* int argc, char* argv[] */) {
	int t, n;
	cin >> t;

	for (int i = 0; i < t; i++) {
		cin >> n;

		int prev, curr, diff, min = (int)10000000000;
		cin >> prev;
		for (int j = 1; j < n; j++) {
			cin >> curr;
			diff = curr - prev;
			prev = curr;

			if (diff < min) {
				min = diff;
			}
		}

		if (min < 0) { cout << 0 << endl; }
		else { cout << min/2 + 1 << endl; }
	}
}
