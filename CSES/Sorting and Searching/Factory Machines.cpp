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

int n; ll t;
vector<ll> ttime;

bool check(ll av) {
	ll curT = t;		//Long long !!!
	for (int i = 0; i < n; i++) {
		curT -= (av / ttime[i]);
		if (curT <= 0) { return true; }
	}
	return curT <= 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> t;
	ttime.resize(n); for (auto &x : ttime) { cin >> x; }

	ll l = 0, r = (ll)1e18 + 5;
	while (l < r) {
		ll mid = (l + r) / 2;
		bool b = check(mid);
		if (b) { r = mid; }
		else { l = mid + 1; }
	}

	cout << l << '\n';
}