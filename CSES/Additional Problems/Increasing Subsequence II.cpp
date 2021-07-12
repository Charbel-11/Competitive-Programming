#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

struct FT {
	int n; vector<ll> vals;
	FT(const int n) : n(n), vals(vector<ll>(n + 1, 0)) { }

	//Adds x
	void update(int i, const ll x) {
		for (++i; i <= n; i += i & -i)
			vals[i] = (vals[i] + x) % mod;
	}
	ll query(int i) const { // sum from 0 ... i
		ll sum = 0;
		for (++i; i; i -= i & -i)
			sum = (sum + vals[i]) % mod;
		return sum;
	}
	ll query(int i, int j) const {		// sum from i ... j
		return (query(j) - query(i - 1) + mod) % mod;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> x(n), comp; 
	for (auto& xx : x) { cin >> xx; comp.push_back(xx); }

	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());
	for (auto& xx : x) { xx = lower_bound(comp.begin(), comp.end(), xx) - comp.begin(); }

	ll ans = 0; FT ft(n);

	for (int i = 0; i < n; i++) {
		ll cur = ft.query(x[i] - 1) + 1;
		ft.update(x[i], cur);
		ans += cur; ans %= mod;
	}

	cout << ans << '\n';
}