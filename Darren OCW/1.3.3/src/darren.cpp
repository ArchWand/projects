#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int n;
	cin >> n;
	int *primes = new int[n];
	int i = 0;

	for (int num = 2; i < n; num++) {
		bool is_prime = true;
		int root = sqrt(num);
		for (int j = 0; j < i && primes[j] <= root; j++) {
			if (num % primes[j] == 0) {
				is_prime = false;
				break;
			}
		}
		if (is_prime) {
			primes[i] = num;
			i++;
		}
	}

	for (int i = 0; i < n; i++) {
		cout << primes[i] << endl;
	}
}
