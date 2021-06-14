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

vector<ll> partial;
void fillP() {
	partial.resize((int)1e6 + 5, 0ll);
	for (int i = 1; i < (int)1e6 + 5; i++) { partial[i] = i + partial[i - 1]; }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	ll x; cin >> x;
	vector<int> days(2 * n + 1, 0);
	for (int i = 0; i < n; i++) {
		int cur; cin >> cur;
		days[i] = days[i + n] = cur;
	}
	
	fillP();

	vector<ll> monthsP(2 * n + 1, 0), daysP(2 * n + 1, 0);
	for (int i = 2 * n - 1; i >= 0; i--) {
		monthsP[i] = partial[days[i]];
		daysP[i] += days[i];
		if (i < 2 * n - 1) { monthsP[i] += monthsP[i + 1]; daysP[i] += daysP[i + 1]; }
	}

	ll res = 0;
	for (int e = 2 * n - 1; e >= n; e--) {
		ll rem = 0;
		rem = daysP[e + 1];

		int l = 0, r = e;
		while (l < r) {
			int mid = (l + r) / 2;
			ll here = daysP[mid] - rem;
			if (here <= x) { r = mid; }
			else { l = mid + 1; }
		}
		ll curRes = 0;

		ll here = daysP[l] - rem;
		if (here <= x) { curRes = monthsP[l] - monthsP[e + 1]; }
		else { l++; }

		ll remX = x - (daysP[l] - rem);
		l--; curRes += partial[days[l]] - partial[days[l] - remX];

		res = max(res, curRes);
	}

	cout << res << endl;
}