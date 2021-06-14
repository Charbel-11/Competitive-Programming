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

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		map<int, ll> freq;
		for (int i = 1; i <= n; i++) {
			int cur; cin >> cur;
			freq[cur - i]++;
		}

		ll ans = 0;
		for (auto& it : freq) {
			ll curF = it.second;
			ans += curF * (curF - 1) / 2;
		}

		cout << ans << '\n';
	}
}
