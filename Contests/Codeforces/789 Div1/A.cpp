#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<int> p(n); for (auto& x : p) { cin >> x; x--; }

		ll ans = 0;
		for (int a = 0; a < n - 3; a++) {
			FT rightFreq(n), leftFreq(n);
			for (int i = a + 2; i < n; i++) { rightFreq.update(p[i], 1); }
			leftFreq.update(p[a + 1], 1);

			ll cumSum = 0;
			for (int c = a + 2; c < n - 1; c++) {
				cumSum += rightFreq.query(0, p[c - 1]);
				cumSum -= leftFreq.query(p[c], n - 1);
				if (p[c] > p[a]) { ans += cumSum; }

				rightFreq.update(p[c], -1);
				leftFreq.update(p[c], 1);
			}
		}

		cout << ans << '\n'; 
	}
}