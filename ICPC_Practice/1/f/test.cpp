#include <bits/stdc++.h>
using namespace std;

void solve() {
	long long n, m;
	cin >> n >> m;

	long long arr[n];
	unordered_map<long long, long long> map;
	for (long long i = 0; i < n; i++) {
		cin >> arr[i];
		if (map.find(arr[i]) != map.end()) map[arr[i]]++;
		else map[arr[i]] = 1;
	}

	for (long long i = 0; i < m; i++) {
		long long ind, val;
		cin >> ind >> val;
		ind--;

		map[arr[ind]]--;
		if (map[arr[ind]] == 0) map.erase(arr[ind]);
		arr[ind] += val;
		if (map.find(arr[ind]) != map.end()) map[arr[i]]++;
		else map[arr[ind]] = 1;

		cout << map.size() << endl;
	}
}

int main(/* int argc, char* argv[] */) {
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		solve();
	}
}
