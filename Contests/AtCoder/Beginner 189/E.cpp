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
	bool op;
	int p, A, B, id;

	query(bool _o, int _p, int _A, int _B, int _id = -1) :op(_o), p(_p), A(_A), B(_B), id(_id) {}
	bool operator < (query& rhs) {
		if (A != rhs.A) { return A < rhs.A; }
		if (op != rhs.op) { return op; }
		return false;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<pair<ll, ll>> pts(n);
	for (auto& p : pts) { cin >> p.first >> p.second; }

	int m; cin >> m;
	vector<query> queries;
	for (int i = 0; i < m; i++) {
		int t; cin >> t;
		if (t <= 2) { queries.push_back(query(true, 0, i, t)); }
		else { int p; cin >> p; queries.push_back(query(true, p, i, t)); }
	}

	int q; cin >> q;
	vector<pair<ll, ll>> ans(q);
	for (int i = 0; i < q; i++) {
		int A, B; cin >> A >> B; A--; B--;
		queries.push_back(query(false, 0, A, B, i));
	}
	sort(queries.begin(), queries.end());

	ll ax, ay, cx, cy;
	ax = ay = 1; cx = cy = 0;
	bool swapped = false;
	for (auto& q : queries) {
		if (!q.op) {
			if (!swapped) ans[q.id] = { pts[q.B].first * ax + cx, pts[q.B].second * ay + cy };
			else ans[q.id] = { pts[q.B].second * ax + cx, pts[q.B].first * ay + cy };
		}
		else {
			if (q.B == 1) {
				swap(ax, ay); swap(cx, cy);
				swapped = !swapped;
				ay = -ay; cy = -cy;
			}
			else if (q.B == 2) {
				swap(ax, ay); swap(cx, cy);
				swapped = !swapped;
				ax = -ax; cx = -cx;
			}
			else if (q.B == 3) {
				ax = -ax; cx = -cx + 2ll * q.p;
			}
			else {
				ay = -ay; cy = -cy + 2ll * q.p;
			}
		}
	}

	for (auto& X : ans) { cout << X.first << ' ' << X.second << '\n'; }
}