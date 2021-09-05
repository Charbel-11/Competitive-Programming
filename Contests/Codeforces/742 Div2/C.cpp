#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	vector<int> numWays(20, 0);
	for (int i = 0; i < 20; i++) {
		int l = 0, r = i;
		while (r >= 0) {
			if (l < 10 && r < 10) { numWays[i]++; }
			l++; r--;
		}
	}

	int t; cin >> t;
	while (t--) {
		string n; cin >> n;
		int numDigits = n.size();
		reverse(n.begin(), n.end());

		int maskLimit = 1;
		if (numDigits > 2) { maskLimit = (1 << (numDigits - 2)); }

		ll ans = 0;
		for (int mask = 0; mask < maskLimit; mask++) {
			ll curWays = 1;

			vector<int> numNeeded(numDigits, 0);
			for (int i = 0; i < numDigits; i++) { numNeeded[i] = n[i] - '0'; }
			for (int i = 0; i < numDigits - 2; i++) {
				if ((mask >> i) & 1) { numNeeded[i] += 10; numNeeded[i + 2]--; }
			}

			for (int i = 0; i < numDigits; i++) { 
				if (numNeeded[i] < 0) { curWays = 0; break; }
				curWays *= numWays[numNeeded[i]];
			}

			ans += curWays;
		}

		cout << ans - 2 << '\n';
	}
}