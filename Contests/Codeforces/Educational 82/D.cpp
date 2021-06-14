#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int pow2(ll num) {
	int ans = 0;
	while (num != 1) {
		num /= 2; ans++;
	}
	return ans;
}

int main() {
	int t; cin >> t;

	while (t--) {
		ll n; cin >> n; int m; cin >> m;
		vector<int> bitsNeeded(65, 0);
		for (int i = 0; i < 64; i++) {
			bitsNeeded[i] = ((n >> i) & 1ll);
		}

		vector<ll> given(65, 0);
		for (int i = 0; i < m; i++) {
			ll cur; cin >> cur;
			given[pow2(cur)]++;
		}

		ll divisions = 0; bool possible = true;
		for (int i = 0; i < 64; i++) {
			if (bitsNeeded[i] == 0) {
				given[i + 1] += given[i] / 2;
				continue;
			}

			if (given[i]) { given[i]--; given[i + 1] += given[i] / 2; continue; }

			for (int j = i + 1; j < 64; j++) {
				if (given[j]) {
					for (int k = j; k > i; k--) {
						given[k - 1] += 2; given[k]--;
						divisions++;
					}
					break;
				}
			}

			if (!given[i]) { possible = false; break; }
			given[i]--; given[i + 1] += given[i] / 2;
		}

		if (!possible) { cout << -1 << endl; continue; }
		cout << divisions << endl;
	}
}
