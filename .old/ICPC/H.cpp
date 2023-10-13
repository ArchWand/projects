#include <bits/stdc++.h>
using namespace std;

#define ll long long

int n, m, a, b;

int main() {
	cin >> n >> m >> a >> b;
	// WANT DISTANCE FROM A TO B
	unordered_map<int, vector<pair<int, int>>> g;
	g.reserve(n);

	int total_dist = 0;
	while (--m) {
		int v, u, c;
		cin >> v >> u >> c;
		g[v].push_back(make_pair(c, u));
		g[u].push_back(make_pair(c, v));
		total_dist += c;
	}

	// MAP OF NODE TO ITS DISTANCE
	unordered_map<int, pair<int, int>> dijk; 
	for (auto i : g)
		dijk[i.first] = make_pair(INT_MAX, INT_MAX);
	dijk[a] = make_pair(0, a);

	queue<pair<int, int>> q; // FIRST IS COST, SECOND IS NODE 
	for(auto i : g[a])
		q.push(i);

	while (!q.empty()) {
		pair<int, int> cur;
		pair<int, int> next = make_pair(INT_MAX, INT_MAX);
		while (!q.empty()) {
			cur = q.front();
			q.pop();
			// update distance values
			if (dijk[cur.second].first < cur.first) {
				dijk[cur.second].first = cur.first;
				// choose shortest distance to look for next
				if (cur.first < next.first) cur = next;
			}
		}
		for(auto i : g[next.second])
			q.push(i);
	}

	cout << "TOTAL DIST: " << total_dist << endl;
	for (auto i : g) {
		cout << "NODE: " << i.first << "\n";
		cout << "\tCost: " << dijk[i.first].first << "\n";
		cout << "\tPrev: " << dijk[i.first].second << "\n";
	}
}
