#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<bool> primes;
void generatePrimes(int n) {
	primes.resize(n, true);
	if (n < 1) { return; }
	primes[0] = false;
	primes[1] = false;

	for (int i = 2; i < n; i++) {
		if (primes[i] == false) {
			continue;
		}

		for (int j = i * 2; j < n; j += i) {
			primes[j] = false;
		}
	}
}

int main() {
	generatePrimes(2002);

	int n;
	cin >> n;

	int m = n;
	while (!primes[m]) {
		m++;
	}

	cout << m << endl;
	for (int i = 1; i < n; i++) {
		cout << i << " " << i + 1 << endl;
	}
	cout << n << " " << 1 << endl;

	int r = m - n;

	for (int i = 1; i < r+1; i++) {
		cout << i << " " << i + (n+1) / 2 << endl;
	}
}
