#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; ll l, r; cin >> n >> l >> r; l--; r--;
		ll limit = (ll)n * (n - 1); bool end1 = false;
		if (r == limit) { r--; end1 = true; }
		if (r < l) { cout << 1 << endl; continue; }

		int start = 1;
		ll curSeries = 2 * (n - 1);
		while (l >= curSeries) {
			l -= curSeries; r -= curSeries;
			start++; curSeries = 2 * (n - start);
		}

		for (ll i = l; i <= r; i++) {
			if (i == curSeries) {
				i -= curSeries; r -= curSeries;
				start++; curSeries = 2 * (n - start);
			}

			if (i % 2 == 0) { cout << start << " "; }
			else { cout << start + (i + 1) / 2 << " "; }
		}
		if (end1) { cout << 1; }
		cout << '\n';
	}
}