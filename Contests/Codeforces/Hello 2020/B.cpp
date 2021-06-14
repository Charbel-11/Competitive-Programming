#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

struct FT {
	int n;
	vector<ll> vals;
	FT(const int n) :
		n(n), vals(vector<ll>(n + 1, 0)) {
	}

	void update(int i) {
		for (++i; i <= n; i += i & -i)
			vals[i] ++;
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
	ll n; cin >> n;
	FT treeMin(10e6+3);
	FT treeMax(10e6+3);

	ll res = 0;
	ll a = 0ll;
	for (int i = 0; i < n; i++) {
		int s; cin >> s;
		int curMin, curMax;
		cin >> curMin; curMin++;
		curMax = curMin;

		bool ascent = false;
		for (int j = 1; j < s; j++) {
			int cur; cin >> cur; cur++;
			if (curMin < cur) { ascent = true; }
			curMin = min(cur, curMin);
			curMax = max(cur, curMax);
		}		

		if (ascent) { 
			res += ((n-a)*2ll)-1; 
			a = a + 1ll;
		}
		else {
			res += treeMin.query(curMax - 1);
			res += treeMax.query(curMin + 1, 10e6+2);
			if (curMin != curMax) { res++; }
			treeMin.update(curMin);
			treeMax.update(curMax);
		}
	}

	cout << res << endl;
}