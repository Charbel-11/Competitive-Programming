#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
typedef long long ll;

int numRobots, bits, cashiers;

struct cashier {
	int maxBits; ll scanTime, pTime;

	cashier(int m, ll s, ll p) : maxBits(m), scanTime(s), pTime(p) {}
};

struct comp {
	bool operator()(const cashier& lhs, const cashier &rhs) {
		return lhs.maxBits > rhs.maxBits;
	}
};

bool check(ll time, multiset<cashier, comp> c) {
	int b = bits, r = numRobots;

	auto it = c.begin();
	while (it != c.end() && b > 0 && r > 0) {
		int curB = min(b, it->maxBits);
		ll timeNeeded = it->scanTime*curB + it->pTime;
		if (time >= timeNeeded) { 
			b -= curB;
			r--;
		}
		else {
			ll possibleBits = (time - it->pTime) / it->scanTime;
			if (possibleBits <= 0) { it++; continue; }

			c.insert(cashier(possibleBits, it->scanTime, it->pTime));
		}

		it++;
	}

	return b == 0;
}

int main() {
	int T; cin >> T;

	for (int z = 0; z < T; z++) {
		cin >> numRobots >> bits >> cashiers;
		multiset<cashier, comp> c;
		for (int i = 0; i < cashiers; i++) {
			int m; ll s, p; cin >> m >> s >> p;
			c.insert(cashier(m, s, p));
		}

		ll l = 0, r = (ll)1e19;
		while (l < r) {
			ll mid = l + (r - l) / 2;
			if (check(mid, c))
				r = mid;
			else
				l = mid + 1;
		}

		cout << "Case #" << z + 1 << ": " << l << endl;
	}
}