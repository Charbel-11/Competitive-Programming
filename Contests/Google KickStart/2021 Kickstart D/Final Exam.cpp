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
		int n, m; cin >> n >> m;

		map<ll, ll> ranges;
		for (int i = 0; i < n; i++) {
			ll l, r; cin >> l >> r;
			ranges[l] = r;
		}
		vector<ll> S(m); for (auto& x : S) { cin >> x; }

		vector<ll> ans(m);
		for (int i = 0; i < m; i++) {
			auto it = ranges.upper_bound(S[i]);
			if (it == ranges.begin()) {
				ll curL = it->first, curR = it->second;
				ans[i] = curL;

				ranges.erase(it); 
				if (curL + 1 <= curR) { ranges.insert({ curL + 1, curR }); }
			}
			else {
				it--;
				ll curL = it->first, curR = it->second;
				if (curR >= S[i]) {
					ans[i] = S[i];
					ranges.erase(it);
					if (curL <= S[i] - 1) { ranges.insert({ curL, S[i] - 1 }); }
					if (S[i] + 1 <= curR) { ranges.insert({ S[i] + 1, curR }); }
				}
				else {
					auto nextIt = next(it);
					if (nextIt == ranges.end()) {
						ans[i] = curR;
						ranges.erase(it);
						if (curL <= curR - 1) { ranges.insert({ curL, curR - 1 }); }
					}
					else {
						ll nextL = nextIt->first, nextR = nextIt->second;

						ll diff1 = S[i] - curR, diff2 = nextL - S[i];
						if (diff1 <= diff2) {
							ans[i] = curR;
							ranges.erase(it);
							if (curL <= curR - 1) { ranges.insert({ curL, curR - 1 }); }
						}
						else if (diff2 < diff1) {
							ans[i] = nextL;
							ranges.erase(nextIt);
							if (nextL + 1 <= nextR) { ranges.insert({ nextL + 1, nextR }); }
						}
					}
				}
			}
		}

		cout << "Case #" << qq << ": ";
		for (auto& x : ans) { cout << x << ' '; } 
		cout << '\n';
	}
}
