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
		ll n, c; cin >> n >> c;
		ll ans = n;

		vector<pair<ll, bool>> pts;
		for (int i = 0; i < n; i++) {
			ll l, r; cin >> l >> r;
			if (r == l + 1) { continue; }
			pts.push_back({ l + 1, 1 });
			pts.push_back({ r, 0 });
		}
		sort(pts.begin(), pts.end());

		map<ll, ll> freq;
		ll cur = pts[0].first, cnt = 1;
		for (int i = 1; i < pts.size(); i++) {
			if (pts[i].first == cur) {
				cnt += (pts[i].second ? 1 : -1);
				continue;
			}

			freq[cnt] += pts[i].first - cur;
			cnt += (pts[i].second ? 1 : -1);
			cur = pts[i].first;
		}

		for (auto it = freq.rbegin(); it != freq.rend() && c > 0; it++) {
			ll curCnt = min(c, it->second);
			ans += curCnt * it->first;
			c -= curCnt;
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}
