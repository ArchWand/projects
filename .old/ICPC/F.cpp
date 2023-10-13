#include <bits/stdc++.h>
using namespace std;

#define ll long long

bool **ar[26] = {0};
bool **sar[26] = {0};

int main() {
	string in;
	int n;
	cin >> n;

	

	//Node* root;
	int count = 0;
	while (n--) {
		cin >> in;

		char a=in[0], b=in[1], c=in[2];
		if (ar[a-'a'] == 0) {
			ar[a-'a'] = new bool*[26];
			for (int i =0; i < 26; ++i) ar[a-'a'][i] = nullptr;
		}
		if (ar[a-'a'][b-'a'] == 0) {
			ar[a-'a'][b-'a'] = new bool[26];
			for (int i =0; i < 26; ++i) ar[a-'a'][b-'a'][i] = false;
		}

		if (sar[a-'a'] == 0) {
			sar[a-'a'] = new bool*[26];
			for (int i =0; i < 26; ++i) sar[a-'a'][i] = nullptr;
		}
		if (sar[a-'a'][c-'a'] == 0) {
			sar[a-'a'][c-'a'] = new bool[26];
			for (int i =0; i < 26; ++i) sar[a-'a'][c-'a'][i] = false;
		}

		ar[a-'a'][b-'a'][c-'a'] = true;
		sar[a-'a'][c-'a'][b-'a'] = true;
	}

	for (int i=0;i<26;++i) if (ar[i])
	for (int j=0;j<26;++j) if (ar[i][j] && ar[j])
	for (int k=0; k<26;++k) if (ar[i][j][k] && ar[k])
	for (int m=0; m<26; ++m) if (ar[i][m] && ar[m]) 
	for (int n=0; n<26; ++n) if (!(m == j && n == k) && ar[i][m][n] && ar[n])
		for (int c=0; c<26; ++c) if (ar[i][c] && ar[j][c] && ar[k][c] && ar[m][c]
							&& !( (k == i && c == j && n == k) || ( k == i && c == m ) ) )
		for (int r=0; r<26; ++r) if (ar[i][c][r] && sar[k][r] && sar[n][r] 
								&& !( (c == j && r == k) || (c == m && r == n) || (i == k && r == n)) )
			for (int p=0; p<26; ++p) if (ar[j][c][p] && ar[n][p][r] &&
									!( (n == i && p == j && r == k) ||
									(n == i && p == m && r == n) ||
									(n == j && p == c && r == p) ||
									(n == i && p == c  ) ||
									(n == k && p == c && r == n) ||
									(j == i && c == j && p == k) ||
									(j == i && c == m && p == n) ||
									(j == i && c == c && p == r) ||
									(j == k && c == c && p == n)))
			for (int q=0; q<26; ++q) if (ar[m][c][q] && ar[k][q][r] &&
										!( (m == i && c == j && q == k) ||
										(m == n && c == p && q == r) ||
										(m == i && c == m && q == n) ||
										(m == j && c == c && q == p) ||
										(m == k && c == q && q == r) ||
										(m == i && c == c && q == r) ||
										(m == k && c == c && q == n) ||
										(k == i && q == j && r == k) ||
										(k == n && q == p && r == r) ||
										(k == i && q == m && r == n) ||
										(k == j && q == c && r == p) ||
										(k == i && q == c && r == r) ||
										(k == k && q == c && r == n)
										)) {
				count++;
				//cout << (char)(i+'a') << " " << (char)(j+'a') << " " << (char)(k+'a') << endl
					 //<< (char)(m+'a') << " " << (char)(c+'a') << " " << (char)(q+'a') << endl
					 //<< (char)(n+'a') << " " << (char)(p+'a') << " " << (char)(r+'a') << endl;
			}

	cout << count << endl;

}
