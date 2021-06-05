#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll; //In case ll is used, be sure to change everything (StVal/update function/vectors...)

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

struct query {
	int type, row;
	int l, r, val;	//l==r if type==0

	query(int _t, int _ro, int _l, int _r, int _v) : type(_t), row(_ro), l(_l), r(_r), val(_v){}
	bool operator<(const query& rhs) {
		if (row == rhs.row) { return type < rhs.type; }
		return row < rhs.row;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> comp;
	vector<query> queries;
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		comp.push_back(x1);	comp.push_back(y1);
		comp.push_back(x2); comp.push_back(y2 + 1);
		if (x1 == x2) {
			queries.push_back(query(0, y1, x1, x1, 1));
			queries.push_back(query(0, y2 + 1, x1, x1, -1));
		}
		else {
			queries.push_back(query(1, y1, x1, x2, 0));
		}
	}
	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());

	for (auto& q : queries) {
		q.row = lower_bound(comp.begin(), comp.end(), q.row) - comp.begin();
		q.l = lower_bound(comp.begin(), comp.end(), q.l) - comp.begin();
		q.r = lower_bound(comp.begin(), comp.end(), q.r) - comp.begin();
	}	
	sort(queries.begin(), queries.end());

	ll ans = 0;
	FT st(comp.size());
	for (auto& q : queries) {
		if (q.type == 0) { st.update(q.l, q.val); }
		else { ans += st.query(q.l, q.r); }
	}
	cout << ans << '\n';
}