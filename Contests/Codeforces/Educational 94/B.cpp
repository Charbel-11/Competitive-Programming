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

	while (t--) {
		ll p, f; cin >> p >> f;
		ll cS, cW; cin >> cS >> cW;
		ll s, w; cin >> s >> w;
		if (s > w) { swap(s, w); swap(cS, cW); }

		ll aS = p / s + f / s;
		if (aS <= cS) { cout << aS << '\n'; continue; }

		ll usedP = p / s, usedF = cS - usedP;
		if (usedF < 0) { usedP = cS; usedF = 0; }

		ll ans = usedP + usedF;
		ll remP = p - usedP * s, remF = f - usedF * s;
		ll aW = remP / w + remF / w; 
		if (aW >= cW) { cout << ans + cW << '\n'; continue; }
		while (true) {
			remF -= s; remP += s;
			if (remP > p || remF < 0) { break; }
			aW = max(aW, remP / w + remF / w);		
			aW = min(aW, cW);
		}
		ans += aW;
		cout << ans << '\n';
	}
}