#include <bits/stdc++.h>
using namespace std;

#define ll long long

int n;

struct a {
	int u;
	int v;
	int c;
	bool operator<(const a& other) {
		if (u != other.u)
			return u < other.u;
		return v < other.v;
	}
};

int main() {
	cin >> n;
	int p;
	vector<vector<int>> v;
	for (int i = 0; i < n; ++i) {
		vector<int> temp;
		for (int j = 0; j < n; ++j) {
			cin >> p;
			temp.push_back(p);
		}
		v.push_back(temp);
	}

	vector<a> a_v;
	for (int i = 0; i < n;++i)
		for (int j = 0; j < n; ++j)
			if (v[i][j] != -1) {
				a s;
				s.u = i + 1;
				s.v = j + 1;
				s.c = v[i][j];
				a_v.push_back(s);
			}

	sort(a_v.begin(), a_v.end());

	cout << a_v.size() << "\n";
	for (auto i : a_v) {
		cout << i.u << " " << i.v << " " << i.c << "\n";
	}

	//for (auto i : v) {
		//for (auto j : i) {
			//cout << j << " ";
		//}
		//cout << endl;
	//}
}
