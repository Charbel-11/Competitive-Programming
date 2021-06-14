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
	for (int qq = 1; qq <= t; qq++) {
		ll G; cin >> G;
		int ans = 0;

		for (ll i = 1; i <= 1e7; i++) {
			ll cur = G - (i - 1) * i / 2;
			if (cur <= 0) { break; }
			if (cur % i == 0) { ans++; }
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}
