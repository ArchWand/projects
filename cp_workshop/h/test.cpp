#include <bits/stdc++.h>
using namespace std;

int main(/* int argc, char* argv[] */) {
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		string word;
		cin >> word;
		stringstream s(word);
		char c;

		int z = 0,
			o = 0;
		while (s >> c) {
			if (c == '0') { z++; }
			else if (c == '1') { o++; }
		}

		int e = min(z, o);

		if (e % 2 == 1) {
			cout << "DA" << endl;
		} else {
			cout << "NET" << endl;
		}
	}
}
