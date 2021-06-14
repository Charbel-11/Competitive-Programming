#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ll n; cin >> n;

	vector <ll> divisors;

	ll d = 2;
	while (d*d <= n) {
		if (n%d == 0) {
			divisors.push_back(d);
			if (d * d != n) { divisors.push_back(n / d); }
		}
		d++;
	}

	if (divisors.empty()) { cout << n << endl; return 0; }

	bool odd = false, even = false;
	for (int i = 0; i < divisors.size(); i++) {
		if (divisors[i] % 2ll == 0) {
			even = true;
		}
		else {
			odd = true;
		}
	}

	if (even && !odd) { cout << 2 << endl; }
	else if (even && odd) {	cout << 1 << endl; }
	else if (!even && odd) { 
		vector<ll> curPrimes;

		for (int i = 0; i < divisors.size(); i++) {
			if (n%divisors[i] == 0) {
				curPrimes.push_back(divisors[i]);
				while (n%divisors[i] == 0) {
					n /= divisors[i];
				}
			}
		}

		if (curPrimes.size() == 1) { cout << curPrimes[0] << endl; }
		else { cout << 1 << endl; }
	}
}