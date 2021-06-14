#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;
typedef long long ll;

int main() {
	int q; cin >> q;

	vector<vector<ll>> lastDigit(10);
	vector<ll> sums(10, 0);
	for (int i = 1; i < 10; i++) {
		set<int> used; used.clear();

		int digit = i;
		while (used.count(i) == 0) {
			used.insert(i);
			lastDigit[digit].push_back(i);
			i += digit; i %= 10;
		}
	}
	for (int i = 1; i < 10; i++) {
		for (int j = 0; j < lastDigit[i].size(); j++) {
			sums[i] += lastDigit[i][j];
		}
	}

	for (int z = 0; z < q; z++) {
		ll n, m; cin >> n >> m;

		if (m > n ) { cout << 0 << endl; continue; }

		ll div = n / m;
		int digit = m % 10;
		if (digit == 0) { cout << 0 << endl; continue; }

		ll res = sums[digit] * (div / ll(lastDigit[digit].size()));
		div %= ll(lastDigit[digit].size());

		int i = 0;
		while (div != 0) {
			res += lastDigit[digit][i];
			i++; div--;
		}

		cout << res << endl;
	}
}