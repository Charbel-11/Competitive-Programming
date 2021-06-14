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
		int a, b, k; cin >> a >> b >> k;
		vector<vector<int>> edges(a);
		
		vector<int> ai(k), bi(k), freqB(b, 0);
		for (auto& x : ai) { cin >> x; x--; }
		for (auto& x : bi) { cin >> x; x--; freqB[x]++; }

		for (int i = 0; i < k; i++) { edges[ai[i]].push_back(bi[i]); }
		
		ll ans = 0;
		for (int i = 0; i < a; i++) {
			for (auto& j : edges[i]) {
				ans += k - (freqB[j] + edges[i].size() - 1);
			}
		}

		cout << ans/2 << '\n';
	}
}