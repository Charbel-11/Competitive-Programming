#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

ll manDist(pair<ll, ll>& p1, pair<ll, ll> p2) {
	return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		ll B, K; cin >> B >> K;
		ll xS, yS, xT, yT; cin >> xS >> yS >> xT >> yT;

		ll ans = (abs(xS - xT) + abs(yS - yT))* K;

		vector<pair<ll, ll>> sStart, sEnd;
		sStart.push_back({ xS, yS - (yS % B) });
		sStart.push_back({ xS, yS + B - (yS % B) });
		sStart.push_back({ xS - (xS % B), yS });
		sStart.push_back({ xS + B - (xS % B), yS });
		sEnd.push_back({ xT, yT - (yT % B) });
		sEnd.push_back({ xT, yT + B - (yT % B) });
		sEnd.push_back({ xT - (xT % B), yT });
		sEnd.push_back({ xT + B - (xT % B), yT });

		for (auto& sP : sStart) {
			for (auto& tP : sEnd) {
				ll curAns = (manDist(sP, { xS, yS }) + manDist(tP, { xT, yT })) * K;
				if ((sP.first % B) == 0 && (sP.second % B) == 0) { curAns += manDist(sP, tP); }
				else if ((tP.first % B) == 0 && (tP.second % B) == 0) { curAns += manDist(sP, tP); }
				else if ((sP.first % B) == 0 && (tP.first % B) == 0 && sP.second / B == tP.second / B) {
					ll c1 = abs(sP.second - tP.second) + abs(tP.first - sP.first) * K;
					pair<ll, ll> special1 = { sP.first, sP.second - (sP.second % B) };
					pair<ll, ll> special2 = { sP.first, sP.second + B - (sP.second % B) };
					ll c2 = manDist(sP, special1) + manDist(special1, tP);
					ll c3 = manDist(sP, special2) + manDist(special2, tP);
					curAns += min({ c1, c2, c3 });
				}
				else if ((sP.second % B) == 0 && (tP.second % B) == 0 && sP.first / B == tP.first / B) {
					ll c1 = abs(sP.first - tP.first) + abs(tP.second - sP.second) * K;
					pair<ll, ll> special1 = { sP.first - (sP.first % B), sP.second };
					pair<ll, ll> special2 = { sP.first + B - (sP.first % B), sP.second};
					ll c2 = manDist(sP, special1) + manDist(special1, tP);
					ll c3 = manDist(sP, special2) + manDist(special2, tP);
					curAns += min({ c1, c2, c3 });
				}
				else {
					curAns += manDist(sP, tP);
				}
				ans = min(ans, curAns);
			}
		}

		cout << ans << '\n';
	}
}
