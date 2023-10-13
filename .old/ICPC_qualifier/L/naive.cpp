#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

long gcd(long a, long b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

string reduce(long a, long b) {
	stringstream ss;
	if (!(a%b)){
		long out = a / b;
		return to_string(out);
	}
	if (a > b) {
		return to_string(1);
	}
	long c = gcd(a, b);
	a /= c;
	b /= c;
	ss << a << "/" << b;
	return ss.str();
}

void taxicab(bool** arr, long w, long t) {
	for (long i = 0; i < w; i++) {
		for (long j = 0; j < w; j++) {
			// Fill diagonal half at distance t
			if (labs(i + j) <= t) {
				arr[i][j] = 1;
			} else {
				arr[i][j] = 0;
			}
		}
	}
}

bool reachable(long i, long j, long s) {
	// diagonal distance
	long d = min(i, j);
	// remaining distance
	long r = max(i, j) - d;

	// Test if 2r + 3d <= 2s
	if (2*r + 3*d <= 2*s) {
		return true;
	} else {
		return false;
	}
}

void spider(bool** arr, long w, long s) {
	// For each valid grid point, test if it is possible to reach the center
	for (long i = 0; i < w; i++) {
		// start on the diag
		long j = w - i;
		do {
			j--;
		} while (!(arr[i][j] && (arr[i][j] = reachable(i, j, s))));
	}
}

long count_arr(bool** arr, long w) {
	long count = 0;
	for (long i = 1; i < w; i++) {
		for (long j = 0; j < w; j++) {
			if (arr[i][j]) {
				count++;
			}
		}
	}
	return count;
}

long triangle(long n) {
	return n * (n + 1) / 2;
}

long spiders(long s) {
	long c = s / 3;
	return (s * (s + 1) + c * (2*s - 3*c - 1)) * 2 + 1;
}

// print arr
void print_arr(bool** arr, long w) {
	for (long i = 0; i < w; i++) {
		for (long j = 0; j < w; j++) {
			// print _ for false and X for true
			cout << (arr[i][j] ? "X" : "_") << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main(int /* argc */, char* /* argv */[]) {
	long t, s;
	cin >> t >> s;
	// Take long absolute value of s
	s = labs(s);
	// width is the max of s and t
	long w = max(s, t) + 1;

	if (t > 2*s + 30) {
		cout << 1 << endl;
		exit(0);
	}

	bool** arr = new bool*[w];
	for (long i = 0; i < w; i++) {
		arr[i] = new bool[w];
	}

	taxicab(arr, w, t);
	spider(arr, w, s);
	long taxi_count = count_arr(arr, w) * 4 + 1;
	long spider_count = spiders(s);

	cout << reduce(taxi_count, spider_count) << endl;
	return 0;
}

