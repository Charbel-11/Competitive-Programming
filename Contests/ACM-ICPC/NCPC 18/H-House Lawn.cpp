#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;

struct Lawnmower {
	string name; ll p, c, t, r; Lawnmower() {}
	Lawnmower(string _s, ll _p, ll _c, ll _t, ll _r) :
		name(_s), p(_p), c(_c), t(_t), r(_r) {}

	bool operator <(const Lawnmower &rhs) const { return p < rhs.p; }
};

vector<Lawnmower> v;

void readLawnmower(string &s) {
	int i = 0, j = 0, n = (int)s.size();
	vector<string> a;
	while (j != n) {
		if (s[j] != ',') { j++; continue; }
		a.push_back(s.substr(i, j - i)); i = j = j + 1;
	}
	a.push_back(s.substr(i, n - i));
	v.push_back(Lawnmower(a[0], stoll(a[1]), stoll(a[2]), stoll(a[3]), stoll(a[4])));
}

bool check(Lawnmower &x, ll l) {
	return ((10080ll * x.c * x.t) / (x.t + x.r)) >= l;
}

int main() {
	ll l; int m; cin >> l >> m;
	string s; getline(cin, s);
	for (int i = 0; i < m; i++) {
		getline(cin, s); readLawnmower(s);
	}
	vector<string> res; ll minPrice = 100001;
	for (int i = 0; i < m; i++) {
		if (!check(v[i], l)) { continue; }
		if (v[i].p > minPrice) { continue; }
		if (v[i].p == minPrice) { res.push_back(v[i].name); continue; }
		res.clear(); res.push_back(v[i].name); minPrice = v[i].p;
	}

	if (res.empty()) { cout << "no such mower" << endl; }
	for (auto &x : res) { cout << x << endl; }
	cin.ignore(2); return 0;

}