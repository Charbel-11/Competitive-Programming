#pragma GCC target("popcnt")
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<bitset<3000>> v(n);
	for (auto& x : v) { cin >> x; }

	ll ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			ll cnt = (v[i] & v[j]).count();
			ans += (cnt * (cnt - 1)) / 2;
		}
	}

	cout << ans << '\n';
}