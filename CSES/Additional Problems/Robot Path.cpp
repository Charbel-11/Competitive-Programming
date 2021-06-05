#include <iostream>
#include <map>
#include <vector>
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

struct query {
	int type, val;
	ll l, r, row;

	query(int _t, ll _ro, ll _l, ll _r, int _v) : type(_t), row(_ro), l(_l), r(_r), val(_v) {}
	bool operator<(const query& rhs) {
		if (row == rhs.row) { return type < rhs.type; }
		return row < rhs.row;
	}
};

vector<pair<pair<ll, ll>, pair<ll, ll>>> segments;
bool intersects(int mid, ll mid2 = -1) {
	vector<ll> curComp;
	vector<query> curQ;
	for (int i = 0; i <= mid; i++) {
		ll x1 = segments[i].first.first, y1 = segments[i].first.second,
			x2 = segments[i].second.first, y2 = segments[i].second.second;

		if (i == mid && mid2 != -1) {
			mid2--;
			if (x1 == x2) {
				if (y2 > y1) { y2 = y1 + mid2; }
				else { y2 = y1 - mid2; }
			}
			else {
				if (x2 > x1) { x2 = x1 + mid2; }
				else { x2 = x1 - mid2; }
			}
		}

		if (x1 > x2) { swap(x1, x2); }
		if (y1 > y2) { swap(y1, y2); }

		curComp.push_back(x1); curComp.push_back(y1);
		curComp.push_back(x2); curComp.push_back(y2 + 1);
		if (x1 == x2) {
			curQ.push_back(query(1, y1, x1, x1, 1));
			curQ.push_back(query(0, y2 + 1, x1, x1, -1));
		}
		else {
			curQ.push_back(query(2, y1, x1, x2, 0));
		}
	}
	sort(curComp.begin(), curComp.end());
	curComp.erase(unique(curComp.begin(), curComp.end()), curComp.end());

	for (auto& q : curQ) {
		q.row = lower_bound(curComp.begin(), curComp.end(), q.row) - curComp.begin();
		q.l = lower_bound(curComp.begin(), curComp.end(), q.l) - curComp.begin();
		q.r = lower_bound(curComp.begin(), curComp.end(), q.r) - curComp.begin();
	}
	sort(curQ.begin(), curQ.end());

	FT st(curComp.size());
	vector<int> ar(curComp.size(), 0);
	int curR = -1; map<int, int> m;
	for (auto& q : curQ) {
		if (q.row > curR) { m.clear(); curR = q.row; }
		if (q.type <= 1) { 
			st.update(q.l, q.val);
			ar[q.l] += q.val;
			if (ar[q.l] > 1) { return true; }
		}
		else {
			auto it = m.lower_bound(q.l);
			if (it != m.end() && q.r >= it->first) { return true; }
			if (it != m.begin() && prev(it)->second >= q.l) { return true; }
			if (st.query(q.l, q.r)) { return true; }
			m[q.l] = q.r;
		}
	}

	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	int revIdx = -1;
	vector<ll> prefS(n, 0);
	ll x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	char prevD = '.';
	for (int i = 0; i < n; i++) {
		char d; int x; cin >> d >> x;
		prefS[i] = (i ? prefS[i - 1] : 0) + x;
		if (d == 'U') { y1++; y2 += x; }
		else if (d == 'D') { y1--; y2 -= x; }
		else if (d == 'L') { x1--; x2 -= x; }
		else { x1++; x2 += x; }
		if (i == 0) { x1 = y1 = 0; }
		if ((d == 'U' && prevD == 'D') || (d == 'D' && prevD == 'U') || (d == 'L' && prevD == 'R') || (d == 'R' && prevD == 'L')) {
			if (revIdx == -1) { revIdx == i; }
		}

		segments.push_back({ {x1,y1},{x2,y2} });
		x1 = x2; y1 = y2; prevD = d;
	}

	int l = 0, r = n;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (intersects(mid)) { r = mid; }
		else { l = mid + 1; }
	}

	ll ans = 0;
	if (l == n) { cout << prefS.back() << '\n'; return 0; }
	if (l == 0) { cout << prefS[0] << '\n'; return 0; }
	ans += prefS[l];
	ll lastLen = prefS[l] - prefS[l - 1];

	ll nL = 1, nR = lastLen;
	while (nL < nR) {
		ll mid = (nL + nR) >> 1;
		if (intersects(l, mid)) { nR = mid; }
		else { nL = mid + 1; }
	}
	ans -= (lastLen - nL);
	if (revIdx == l) { ans--; }

	cout << ans << '\n';
}