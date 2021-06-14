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

void normalize(pair<ll, ll>& p) {
	ll g = gcd(p.first, p.second);
	p.first /= g;
	p.second /= g;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll n, m;
	int q;
	cin >> n >> m >> q;

	ll d;
	pair<ll, ll> smallerDen;
	bool nSmaller;
	if (n > m) {
		nSmaller = false;
		d = n;
		smallerDen = { m, d };
	}
	else {
		nSmaller = true;
		d = m;
		smallerDen = { n, d };
	}
	normalize(smallerDen);

	//n inner; m outer
	for (int z = 0; z < q; z++) {
		ll sx, sy, ex, ey;
		cin >> sx >> sy >> ex >> ey;

		ll start, end;
		if ((sx == 1 && !nSmaller) || (sx==2 && nSmaller)) {
			start = (sy * smallerDen.first + smallerDen.second - 1) / smallerDen.second;
		}
		else { start = sy; }
		if ((ex == 1 && !nSmaller) || (ex == 2 && nSmaller)) {
			end = (ey * smallerDen.first + smallerDen.second - 1) / smallerDen.second;
		}
		else{end = ey;}

		if (end < start) {
			ll temp = start;
			start = end;
			end = temp;
		}

		if (end - start >= smallerDen.first || start % smallerDen.first > end % smallerDen.first) {
			cout << "NO" << endl; continue;
		}
		cout << "YES" << endl;
	}
}