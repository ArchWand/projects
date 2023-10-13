#include <bits/stdc++.h>
using namespace std;

#define ll long long

enum BASE {
	A = 0,
	T,
	G,
	C
};

struct thing {
	int v;
	BASE c;
	bool operator<(const thing& other) {
		if (v != other.v)
			return v > other.v;
		return c < other.c;
	}
};

int main() {
	string in;
	cin >> in;
	
	// ar[in.size+1][4]
	int** ar = new int*[in.size()+1];
	for (int i = 0; i <= in.size(); ++i) {
		ar[i] = new int[4];
	}

	ar[0][BASE::A] = 0;
	ar[0][BASE::T] = 0;
	ar[0][BASE::G] = 0;
	ar[0][BASE::C] = 0;
	for (int i = 1; i <= in.size(); ++i) {
		ar[i][BASE::A] = ar[i-1][BASE::A];
		ar[i][BASE::T] = ar[i-1][BASE::T];
		ar[i][BASE::G] = ar[i-1][BASE::G];
		ar[i][BASE::C] = ar[i-1][BASE::C];

		if (in[i-1] == 'A') ++ar[i][BASE::A];
		if (in[i-1] == 'T') ++ar[i][BASE::T];
		if (in[i-1] == 'G') ++ar[i][BASE::G];
		if (in[i-1] == 'C') ++ar[i][BASE::C];
	}

	//for (int i = 0; i <= in.size(); i++) {
		//std::cout << ar[i][BASE::A] << " "
				  //<< ar[i][BASE::T] << " "
				  //<< ar[i][BASE::G] << " "
				  //<< ar[i][BASE::C] << " "
				  //<< endl;

	//}

	int n;
	cin >> n;
	while (n--) {
		int st, end;
		cin >> st >> end;

		st--;

		int ai=ar[end][BASE::A]-ar[st][BASE::A], 
			ti=ar[end][BASE::T]-ar[st][BASE::T], 
			gi=ar[end][BASE::G]-ar[st][BASE::G], 
			ci=ar[end][BASE::C]-ar[st][BASE::C];

		thing a;
		a.v = ai;
		a.c = BASE::A;
		thing t;
		t.v = ti;
		t.c = BASE::T;
		thing g;
		g.v = gi;
		g.c = BASE::G;
		thing c;
		c.v = ci;
		c.c = BASE::C;
		vector<thing> v;
		v.push_back(a);
		v.push_back(t);
		v.push_back(g);
		v.push_back(c);

		//for (int i = 0; i < v.size(); i++) {
			//cout << "Count: " << v[i].v << endl;
		//}

		sort(v.begin(), v.end());

		for (auto i : v) {
			switch (i.c) {
			case BASE::A:
				cout << "A";
				break;
			case BASE::T:
				cout << "T";
				break;
			case BASE::G:
				cout << "G";
				break;
			case BASE::C:
				cout << "C";
				break;
			default:
				break;
			}
		}
		cout << "\n";
	}

}
