#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long

int main(/* int argc, char* argv[] */) {
	int n, m, x, k;
	cin >> n >> m >> x >> k;

	bool b[n*m];
	char c;
	for (int i = 0; i < n*m; i++) {
		cin >> c;
		if (c == '#') b[i] = true;
		else b[i] = false;
	}
}
