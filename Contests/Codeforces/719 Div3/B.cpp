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
		ll n; cin >> n;

		int ans = 0;
		for (int k = 1; k <= 9; k++) {
			ll cur = k;
			while (cur <= n) { ans++; cur *= 10; cur += k; }
		}

		cout << ans << '\n';
	}
}
