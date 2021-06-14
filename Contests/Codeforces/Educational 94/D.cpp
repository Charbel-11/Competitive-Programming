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
		int n; cin >> n;
		vector<ll> a(n), freq1(n + 1, 0), freq2(n + 1, 0);
		for (auto &x : a) { cin >> x; }

		ll ans = 0, cur = 0;
		for (int i = 0; i < n - 3; i++) {
			freq1.clear(); freq1.resize(n + 1, 0);
			freq2.clear(); freq2.resize(n + 1, 0);
			for (int j = i + 3; j < n; j++) { freq2[a[j]]++; }
			freq1[a[i + 1]]++; cur = freq2[a[i + 1]];
			if (a[i] == a[i + 2]) { ans += cur; }

			for (int j = i + 3; j < n; j++) {
				cur -= freq1[a[j]];
				freq2[a[j]]--; freq1[a[j - 1]]++;
				cur += freq2[a[j - 1]];

				if (a[i] == a[j]) { ans += cur; }
			}
		}

		cout << ans << '\n';
	}
}