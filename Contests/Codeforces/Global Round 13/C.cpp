#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int maxIdx(vector<ll>& a) {
	int idx = 0; ll curM = a[0];
	for(int i = 1; i < a.size(); i++){
		if (curM < a[i]) { curM = a[i]; idx = i; }
	}
	return idx;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<ll> S(n); for (auto& x : S) { cin >> x; }

		vector<ll> bonus(n, 0);
		ll ans = 0;
		for (int i = 0; i < n; i++) {
			int idx = maxIdx(S);
			if (S[idx] == 1) { break; }
			ll curCost = S[idx] - 1;

			vector<ll> prefS(n + 5, 0);
			prefS[idx] = curCost; prefS[idx + 1] = -curCost;
			for (int j = idx; j < n; j++) {
				if (j) { prefS[j] += prefS[j - 1]; }
				if (prefS[j] == 0) { continue; }

				if (bonus[j]) { 
					ll saved = min(bonus[j], prefS[j]);
					bonus[j] -= saved; ans -= saved; prefS[j] -= saved; prefS[j + 1] += saved;
				}
				if (prefS[j] == 0) { continue; }

				int r = j + S[j];
				int l = r - prefS[j] + 1;
				if (l < n) {
					if (l <= j) {
						ll add = j - l + 1;
						prefS[j + 1] += add; prefS[j + 2] -= add;
						l = j + 1;
					}
					prefS[l]++;
					if (r + 1 < n) { prefS[r + 1]--; }
				}

				S[j] -= prefS[j];
				S[j] = max(S[j], 1ll);
			}

			ans += curCost;
			bonus[idx] += curCost;
		}

		cout << ans << '\n';
	}
}