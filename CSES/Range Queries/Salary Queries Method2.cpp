#include <vector>
#include <string>
#include <assert.h>
#include <iostream>
#include <algorithm>
using namespace std;

struct FT {
	int n;
	vector<int> vals;
	FT(const int n) :
		n(n), vals(vector<int>(n + 1, 0)) {
	}

	//Adds x
	void update(int i, const int x) {
		for (++i; i <= n; i += i & -i)
			vals[i] += x;
	}
	int query(int i) const { // sum from 0 ... i
		int sum = 0;
		for (++i; i; i -= i & -i)
			sum += vals[i];
		return sum;
	}
	int query(int i, int j) const {		// sum from i ... j
		return query(j) - (i ? query(i - 1) : 0);
	}
};

struct qq {
	bool op; int a, b; qq() {}
	qq(bool _op, int _a, int _b): op(_op), a(_a), b(_b) {}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	vector<int> comp;

	int n, q; cin >> n >> q;
	vector<int> salaries(n);
	for (auto &x : salaries) { cin >> x; comp.push_back(x); }

	vector<qq> queries(q);
	for (int i = 0; i < q; i++) {
		string op; cin >> op;
		bool b = (op == "!");
		int x, y; cin >> x >> y;
		queries[i] = qq(b, x, y);

		if (!b) { comp.push_back(x); }
		comp.push_back(y);
	}

	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());

	for (int i = 0; i < n; i++) { salaries[i] = lower_bound(comp.begin(), comp.end(), salaries[i]) - comp.begin(); }
	for (int i = 0; i < q; i++) {
		if (!queries[i].op) { queries[i].a = lower_bound(comp.begin(), comp.end(), queries[i].a) - comp.begin(); }
		queries[i].b = lower_bound(comp.begin(), comp.end(), queries[i].b) - comp.begin();
	}

	FT ft(comp.size() + 1);
	for (int i = 0; i < n; i++) { ft.update(salaries[i], 1); }
	for (int i = 0; i < q; i++) {
		if (queries[i].op) {
			int k = queries[i].a - 1, x = queries[i].b;
			ft.update(salaries[k], -1);
			salaries[k] = x;
			ft.update(salaries[k], 1);
		}
		else {
			cout << ft.query(queries[i].a, queries[i].b) << '\n';
		}
	}
}