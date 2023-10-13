#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> s;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		s.push_back(a);
	}

	sort(s.begin(), s.end());

	int t = 0;
	while (s.size() != 1) {
		int a = *s.begin();
		s.erase(s.begin());
		int b = *s.begin();
		s.erase(s.begin());

		s.push_back(a + b);
		sort(s.begin(), s.end());
		t += a + b;
	}

	cout << t << endl;
}
