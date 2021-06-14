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

ll evaluate(ll x, ll y, ll z) {
	return (x - y)*(x - y) + (x - z)*(x - z) + (y - z)*(y - z);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int nr, ng, nb; cin >> nr >> ng >> nb;
		vector<ll> r(nr), g(ng), b(nb);
		for (auto &x : r) { cin >> x; }
		for (auto &x : g) { cin >> x; }
		for (auto &x : b) { cin >> x; }
		sort(r.begin(), r.end());
		sort(g.begin(), g.end());
		sort(b.begin(), b.end());

		int i = 0, j = 0, k = 0;
		ll ans = LLONG_MAX;
		while (i < nr && j < ng && k < nb) {
			ll cur = evaluate(r[i], g[j], b[k]);
			ans = min(ans, cur);
			ll nextMove1, nextMove2, nextMove3;
			nextMove1 = nextMove2 = nextMove3 = LLONG_MAX;
			if (i < nr - 1) { nextMove1 = evaluate(r[i + 1], g[j], b[k]); }
			if (j < ng - 1) { nextMove2 = evaluate(r[i], g[j + 1], b[k]); }
			if (k < nb - 1) { nextMove3 = evaluate(r[i], g[j], b[k + 1]); }
			if (nextMove1 < nextMove2 && nextMove1 < nextMove3) { i++; continue; }
			if (nextMove2 < nextMove3) { j++; continue; }
			k++;
		}

		cout << ans << endl;
	}
}