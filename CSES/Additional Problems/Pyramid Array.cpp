#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

struct FT {
	int n;
	vector<ll> vals;
	FT(const int n) : n(n), vals(vector<ll>(n + 1, 0)) { }

	//Adds x
	void update(int i, const ll x) {
		for (++i; i <= n; i += i & -i)
			vals[i] += x;
	}
	ll query(int i) const { // sum from 0 ... i
		ll sum = 0;
		for (++i; i; i -= i & -i)
			sum += vals[i];
		return sum;
	}
	ll query(int i, int j) const {		// sum from i ... j
		return query(j) - query(i - 1);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> x(n); for (auto& xx : x) { cin >> xx; }

	vector<pair<int, int>> pos(n);
	for (int i = 0; i < n; i++) {
		pos[i] = { x[i], i };
	}
	sort(pos.begin(), pos.end());

	FT ft(n);
	for (int i = 0; i < n; i++) { ft.update(i, 1); }

	ll ans = 0;
	for (int i = 0; i < n; i++) {
		int curPos = pos[i].second;
		ft.update(curPos, -1);
		ans += min(ft.query(0, curPos), ft.query(curPos, n - 1));
	}

	cout << ans << '\n';
}