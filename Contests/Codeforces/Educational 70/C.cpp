#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

pair<int, int> prod(int num) {
	int a = 2, b = int(sqrt(num));

	while (a <= b) {
		if (num%a == 0) { return { a, num / a }; }
		a++;
	}

	return { -1, -1 };
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int T;
	cin >> T;

//	generatePrimes(int(1e9));

	for (int z = 0; z < T; z++) {
		int n;
		cin >> n;

		pair<int, int> temp = prod(n);

		if (temp.first != -1 && temp.second != -1) {
			cout << '1'*temp.first << "33" << 7 * temp.second << endl;
		}
		else {

		}
	}
}