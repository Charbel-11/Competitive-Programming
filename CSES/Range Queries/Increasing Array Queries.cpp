#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

struct query {
	int l, r, id;;
	query(int _l, int _r, int _id) :l(_l), r(_r), id(_id) {}
	bool operator<(const query& rhs) {
		return l > rhs.l;
	}
};

struct interval {
	int l, r;
	ll val, sufVal;
	interval() {}
	interval(int _l, int _r, ll _v, ll _s) :l(_l), r(_r), val(_v), sufVal(_s) {}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q;
	vector<ll> a(n), sS(n + 1, 0); for (auto& x : a) { cin >> x; }
	for (int i = n - 1; i >= 0; i--) { sS[i] = sS[i + 1] + a[i]; }	

	vector<query> queries;
	for (int i = 0; i < q; i++) {
		int l, r; cin >> l >> r; l--; r--;
		queries.push_back(query(l, r, i));
	}
	sort(queries.begin(), queries.end());

	int i = 0; vector<ll> ans(q); 
	map<int, interval> m;	//start idx -> interval
	m[n] = interval(n, n, 1e12, 0);
	for (int l = n - 1; l >= 0; l--) {
		int curEnd = l;
		while (m.begin()->second.val <= a[l]) {
			curEnd = m.begin()->second.r;
			m.erase(m.begin());
		}

		ll range = curEnd - l + 1;
		ll curSufVal = range * a[l] + m.begin()->second.sufVal;
		m[l] = interval(l, curEnd, a[l], curSufVal);
	
		while (i < q && queries[i].l == l) {
			int r = queries[i].r;
			ll curA = curSufVal - sS[l] + sS[r + 1];
			auto it = prev(m.upper_bound(queries[i].r));
			curA -= it->second.sufVal;
			curA += (r - it->second.l + 1) * it->second.val;
			ans[queries[i].id] = curA; 	i++;
		}
	}

	for (auto& x : ans) { cout << x << '\n'; }
}