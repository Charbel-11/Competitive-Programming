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
const ll mod = 1e9 + 7;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n, k; cin >> n >> k;
		string s; cin >> s;
		ll ans = 0;

		vector<ll> powK(n + 1, 1);
		for (int i = 1; i < n + 1; i++) {
			powK[i] = powK[i - 1] * k;
			powK[i] %= mod;
		}

		int free = (n + 1) / 2;
		for (int i = 0; i < free; i++) {
			for (int j = 0; j < s[i] - 'a'; j++) {
				int rem = free - i - 1;
				ans += powK[rem]; ans %= mod;
			}
		}

		string s2 = s;
		for (int i = 0; i < n/2; i++) {
			s2[n - i - 1] = s2[i];
		}
		if (s2 < s) { ans++; ans %= mod; }

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}
