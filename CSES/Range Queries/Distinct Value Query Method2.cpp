#include <vector>
#include <string>
#include <assert.h>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;
typedef long long ll;

struct FT {
	int n;
	vector<ll> vals;
	FT(const int n) :
		n(n), vals(vector<ll>(n + 1, 0)) {
	}

	//Adds x
	void update(int i, const ll x) {
		for (++i; i <= n; i += i & -i)
			vals[i] += x;
	}
	ll query(int i) const { // sum from 0 ... i
		assert(i >= -1 && i < n);
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

	int n, q; cin >> n >> q;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }

	vector<pair<pair<int, int>, int>> queries(q); int id = 0;
	for (auto &p : queries) { 
		cin >> p.first.first >> p.first.second;
		p.first.first--; p.first.second--; 
		p.second = id++; 
	}
	sort(queries.rbegin(), queries.rend());

	FT st(n + 1); map<int, int> m;
	vector<int> ans(q);
	int l = n, r = n;
	for (auto &p : queries) {
		while (l != p.first.first) {
			l--; 
			if (m.count(nums[l])) { st.update(m[nums[l]], -1); }
			m[nums[l]] = l; st.update(l, 1);
		}

		ans[p.second] = st.query(p.first.second);
	}
	
	for (auto &x : ans) { cout << x << '\n'; }
}