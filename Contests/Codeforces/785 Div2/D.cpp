#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }

bool elementInProgression(ll a, ll r, ll n, ll x) {
	if (x < a) { return false; }
	if (((x - a) % r) != 0) { return false; }

	ll lastA = a + r * (n - 1);
	if (x > lastA) { return false; }

	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		ll b0, rb, nb; cin >> b0 >> rb >> nb;
		ll c0, rc, nc; cin >> c0 >> rc >> nc;

		ll lastB = b0 + rb * (nb - 1), lastC = c0 + rc * (nc - 1);

		if (!elementInProgression(b0, rb, nb, c0) || ((rc % rb) > 0) || !elementInProgression(b0, rb, nb, lastC)) {
			cout << 0 << '\n'; continue;
		}

		vector<ll> div;
		ll ans = 0, d = 1;
		while (d * d <= rc) {
			if ((rc % d) == 0) { 
				div.push_back(d);
				if (d != rc / d) { div.push_back(rc / d); }
			}
			d++;
		}

		for(auto &ra : div){
			ll LCM = lcm(ra, rb);
			if (LCM != rc) { continue; }

			ll mustHaveElements = 1 + (lastC - c0) / ra;
			ll curFirst = c0, curLast = lastC;

			ll nextCommonRight = curLast + LCM, nextCommonLeft = curFirst - LCM;
			if (nextCommonRight > lastB || nextCommonLeft < b0) { ans = -1; break; }

			ll choices = LCM / ra;
			ans = ans + ((choices * choices) % mod); ans %= mod;
		}

		cout << ans << '\n';
	}
}