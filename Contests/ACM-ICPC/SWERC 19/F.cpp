#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<pair<ll, ll>> p;		//points in clockwise order
int n;

//Polygon area * 2, need the points in clockwise order
ll area() {
	ll a = 0;
	for (int i = 0; i < n; i++) {
		a += (p[i].first * p[(i + 1) % n].second - p[(i + 1) % n].first * p[i].second);
	}
	return abs(a);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	ll ans = 0;
	while (t--) {
		cin >> n;
		p.clear(); p.resize(n);
		for (auto& pt : p) { cin >> pt.first >> pt.second; }

		ans += area();
	}

	cout << ans / 2 << '\n';
}