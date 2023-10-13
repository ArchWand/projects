#include <iostream>
#include <string>
#include <sstream>
using namespace std;

unsigned long gcd(unsigned long a, unsigned long b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

string reduce(unsigned long a, unsigned long b) {
	stringstream ss;
	if (!(a%b)){
		unsigned long out = a / b;
		return to_string(out);
	}
	if (a > b) {
		return to_string(1);
	}
	unsigned long c = gcd(a, b);
	a /= c;
	b /= c;
	ss << a << "/" << b;
	return ss.str();
}

unsigned long triangle(unsigned long n) {
	return n * (n + 1) / 2;
}

unsigned long taxicab(unsigned long n) {
	return triangle(n) * 4 + 1;
}

unsigned long quarter_spider(unsigned long s) {
	unsigned long c = s / 3;
	return (s * (s + 1) + c * (2*s - 3*c - 1)) / 2;
}

unsigned long spider(unsigned long s) {
	return quarter_spider(s) * 4 + 1;
}

int main(int /* argc */, char* /* argv */[]) {
	unsigned long t, s;
	cin >> t >> s;

	cout << reduce (taxicab(t), spider(s)) << endl;
	return 0;
}

