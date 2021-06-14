#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a%b);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll n, m;
	int q;
	cin >> n >> m >> q;

	vector<ll> perSection = { n, m };
	ll g = gcd(perSection[0], perSection[1]);
	perSection[0] /= g;
	perSection[1] /= g;

	for (int z = 0; z < q; z++) {
		ll sx, sy, ex, ey;
		cin >> sx >> sy >> ex >> ey;
	
		ll c1 = (sy-1) / perSection[sx - 1];
		ll c2 = (ey-1) / perSection[ex - 1];

		if (c1 == c2) { cout << "YES" << endl; }
		else { cout << "NO" << endl; }
	}
}