#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

int main() {
	int a, b, c;
	cin >> a >> b >> c;

	int ans[16]=  {INT_MAX, INT_MAX, INT_MAX, INT_MAX,
		INT_MAX, INT_MAX, INT_MAX, INT_MAX,
		INT_MAX, INT_MAX, INT_MAX, INT_MAX,
		INT_MAX, INT_MAX, INT_MAX, INT_MAX};

	ans[0] = a + b + c;
	ans[1] = a + b - c;
	ans[2] = a - b + c;
	ans[3] = (a * b) + c;
	ans[4] = (a + b) * c;
	ans[5] = (a * b) - c;
	ans[6] = (a - b) * c;
	ans[7] = a - b - c;
	ans[8] =  a*b*c;
	if (a % b == 0) {
		ans[9] = (a / b) + c;
		ans[10] = (a / b) - c;
		ans[11] = (a / b) * c;
	}
	if (a % b == 0 && (a/b) % c == 0) {
		ans[12]= (a / b) / c;
	}
	if ((a + b) % c == 0) {
		ans[13] = (a + b) / c;
	}
	if ((a - b) % c == 0) {
		ans[14] = (a - b) / c;
	}
	if ((a * b) % c == 0) {
		ans[15] = (a * b) / c;
	}

	int out = INT_MAX;
	for (auto i : ans) {
		if (i < out && i >= 0) {
			out = i;
		}
	}

	cout << out << endl;

	return 0;
}
