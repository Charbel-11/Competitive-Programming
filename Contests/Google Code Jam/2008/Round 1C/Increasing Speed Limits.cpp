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
const ll mod = 1e9 + 7;

struct FT {
	int n;
	vector<ll> vals;
	FT(const int n) : n(n), vals(vector<ll>(n + 1, 0)) { }

	//Adds x
	void update(int i, const ll x) {
		for (++i; i <= n; i += i & -i) {
			vals[i] += x;
			vals[i] %= mod;
		}
	}
	ll query(int i) const { // sum from 0 ... i
		ll sum = 0;
		for (++i; i; i -= i & -i) {
			sum += vals[i];
			sum %= mod;
		}
		return sum;
	}
	ll query(int i, int j) const {		// sum from i ... j
		return query(j) - query(i - 1);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n, m; cin >> n >> m;
		ll X, Y, Z; cin >> X >> Y >> Z;
		vector<ll> A(m), num(n), comp; 
		for (int i = 0; i < m; i++) { cin >> A[i]; }
		for (int i = 0; i < n; i++) {
			num[i] = A[i % m];
			comp.push_back(num[i]);
			A[i % m] = (X * A[i % m] + Y * (i + 1)) % Z;
		}
		sort(comp.begin(), comp.end());
		comp.erase(unique(comp.begin(), comp.end()), comp.end());

		for (auto& x : num) { x = lower_bound(comp.begin(), comp.end(), x) - comp.begin(); }
		FT ft(comp.size());
		ll ans = 0;
		for (int i = 0; i < n; i++) {
			ll cur = ft.query(num[i] - 1) + 1;
			ans += cur; ans %= mod;
			ft.update(num[i], cur);
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}