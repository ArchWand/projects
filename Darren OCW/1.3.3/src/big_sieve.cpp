#include <iostream>
using namespace std;
#define ull unsigned long long

ull log2(ull n) {
	ull i = 0;
	while (n >>= 1) i++;
	return i;
}

// Find the first n primes
int main() {
	// Get input
	ull n;
	cin >> n;

	// Initialize array
	ull len = n * log2(n) * 1.15; // Approximate length
	if (len < 8) len = 8;
	bool *primes = new bool[len];

	for (ull i = 0; i < len; i++) primes[i] = true;
	primes[0] = primes[1] = false;

	// Sieve
	for (ull i = 2; i < len; i++) {
		if (primes[i]) {
			cout << i << '\n';
			if (--n == 0) break;

			for (ull j = i * 2; j < len; j += i) {
				primes[j] = false;
			}
		}
	}
}
