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

struct Frac {
	ll num, denum; Frac() {}
	ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
	Frac(ll _n, ll _d) {
		ll g = gcd(abs(_n), abs(_d));
		num = abs(_n) / g; denum = abs(_d) / g;
		if ((_n < 0) ^ (_d < 0)) { num = -num; }
	}
	Frac(ll x) : num(x), denum(1) {}
	Frac operator *(const Frac& rhs) { return Frac(num * rhs.num, denum * rhs.denum); }
	Frac operator +(const Frac& rhs) { return Frac(num * rhs.denum + denum * rhs.num, denum * rhs.denum); }
	Frac operator -(const Frac& rhs) { return Frac(num * rhs.denum - denum * rhs.num, denum * rhs.denum); }
	Frac operator /(const Frac& rhs) { return Frac(num * rhs.denum, denum * rhs.num); }
	Frac operator +=(const Frac& rhs) { return (*this) = (*this) + rhs; }
	Frac operator -=(const Frac& rhs) { return (*this) = (*this) - rhs; }
	Frac operator *=(const Frac& rhs) { return (*this) = (*this) * rhs; }
	Frac operator /=(const Frac& rhs) { return (*this) = (*this) / rhs; }
	bool operator ==(const Frac& rhs) const { return num == rhs.num && denum == rhs.denum; }
	bool operator <(const Frac& rhs) const { return num * rhs.denum < denum* rhs.num; }
	bool operator >(const Frac& rhs) const { return num * rhs.denum > denum * rhs.num; }
};


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n, q; cin >> n >> q;
		vector<string> answers(n); vector<int> scores(n);
		for (int i = 0; i < n; i++) {
			cin >> answers[i] >> scores[i];
		}

		vector<string> candidates;
		for (int i = 0; i < (1 << q); i++) {
			bool OK = true;

			for (int j = 0; j < n; j++) {
				int match = 0;
				for (int k = 0; k < q; k++) {
					if ((1 << k) & i) {
						if (answers[j][k] == 'T') { match++; }
					}
					else {
						if (answers[j][k] == 'F') { match++; }
					}
				}
				if (match != scores[j]) { OK = false; }
			}

			if (OK) {
				string curAns = "";
				for (int k = 0; k < q; k++) {
					if ((1 << k) & i) { curAns.push_back('T'); }
					else { curAns.push_back('F'); }
				}
				candidates.push_back(curAns);
			}
		}

		Frac p(1, candidates.size());
		string ans = ""; Frac best(0, 1);
		for (int i = 0; i < (1 << q); i++) {
			Frac expected(0, 1);

			string curAns = "";
			for (auto& candidate : candidates) {
				curAns = "";
				int curScore = 0;
				for (int k = 0; k < q; k++) {
					if ((1 << k) & i) {
						curAns.push_back('T');
						if (candidate[k] == 'T') { curScore++; }
					}
					else {
						curAns.push_back('F');
						if (candidate[k] == 'F') { curScore++; }
					}
				}

				Frac tmp(curScore, 1);
				tmp = tmp * p;
				expected += tmp;
			}

			if (expected > best) { best = Frac(expected.num, expected.denum); ans = curAns; }
		}

		cout << "Case #" << qq << ": " << ans << " " << best.num << "/" << best.denum << '\n';
	}
}