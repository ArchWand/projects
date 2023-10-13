#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long

int len, k;
char* buf;
bool risk['z'+1];

int next_risk(int start) {
	for (int i = start; i < len; i++) {
		if (risk[(int)buf[i]]) { return i; }
	}
	return -1;
}

bool chunk(int &start, int &rstart, int &rend, int &end) {
	// cout << "chunk(" << start << ", " << rstart << ", " << rend << ", " << end << ")" << endl;

	rstart = next_risk(start);
	if (rstart == -1) { return false; }
	if (rend <= rstart) {
		rend = rstart;
		for (int c = 1; c < k; c++) {
			rend = next_risk(rend+1);
			if (rend == -1) { return false; }
		}
	} else {
		rend = end + 1;
	}
	if (rend == -1) { return false; }

	end = next_risk(rend+1);
	if (end == -1) {
		end = len - 1;
	} else {
		end--;
	}

	return true;
}

int main() {
	int l;
	cin >> len >> k >> l;

	buf = new char[len];
	cin >> buf;

	for (int i = 0; i < 'z'+1; risk[i++] = 0);
	for (int i = 0; i < l; i++) {
		char c;
		cin >> c;
		risk[(int)c] = true;
	}

	int start = 0, rstart = -1, rend = 0, end = 0;
	int sum = 0;
	while (chunk(start, rstart, rend, end)) {
		// cout << start << " " << rstart << " " << rend << " " << end << endl;
		// cout << buf << endl;
		// for (int i = 0; i < len; i++) {
			// if (i == start || i == rstart || i == rend || i == end) {
				// cout << "|";
			// } else {
				// cout << " ";
			// }
		// }
		// cout << endl;
		// cout << "sum += " << (rstart - start + 1) << " * " << (end - rend + 1) << " = " << (rstart - start + 1) * (end - rend + 1) << endl;

		sum += (rstart - start + 1) * (end - rend + 1);

		start = rstart + 1;
	}

	cout << sum << endl;
}
