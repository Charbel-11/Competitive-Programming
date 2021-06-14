#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		ll k; cin >> k;
		vector<ll> a(n);
		for (auto &x : a) { cin >> x; }
		
		set<int> used;
		bool OK = true;
		for (int i = 0; i < n; i++) {
			if (a[i] == 0) { continue; }

			int power = 0;
			while (a[i]) {
				ll cur = a[i] % k;
				if (cur) {
					if (used.count(power) || cur > 1) { OK = false; break; }
					used.insert(power);
				}
				a[i] /= k; power++;
			}
			if (!OK) { break; }
		}

		cout << (OK ? "YES" : "NO") << endl;
	}
}