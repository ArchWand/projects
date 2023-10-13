#include <bits/stdc++.h>
using namespace std;

int main(/* int argc, char* argv[] */) {
	int n;
	cin >> n;
	int out = 2 * n / 3;
	if (n % 3 == 1) out++;
	cout << out;
}
