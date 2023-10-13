#include <iostream>
#include <cmath>
using namespace std;

// Find the first n primes
int main() {
	// Get input
	int n;
	cin >> n;

	// Cache
	int *cache = new int[n];

	// Find primes
	int count = 0;
	for (int i = 2; count < n; i++) {
		// Check if prime
		bool prime = true;
		int root = sqrt(i);
		for (int j = 0; j < count && cache[j] <= root; j++) {
			if (i % cache[j] == 0) {
				prime = false;
				break;
			}
		}

		// Add to cache and print
		if (prime) {
			cache[count] = i;
			cout << i << '\n';
			count++;
		}
	}
}
