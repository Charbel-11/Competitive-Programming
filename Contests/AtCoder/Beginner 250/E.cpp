#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> a(n); for (auto& x : a) { cin >> x; }
	vector<int> b(n); for (auto& x : b) { cin >> x; }

	vector<pair<int, int>> equalRange(n, { -1,-1 });
	set<int> A, B, ANotB; int lB = -1, rB = -1;
	for (int i = 0; i < n; i++) {
		if (!A.count(a[i])) {
			A.insert(a[i]);
			if (!B.count(a[i])) { ANotB.insert(a[i]); }
		}

		while (rB < n - 1 && !ANotB.empty()) {
			rB++;
			if (!B.count(b[rB])) {
				lB = rB; B.insert(b[rB]);
				if (ANotB.count(b[rB])) { ANotB.erase(b[rB]); }
			}
		}
		if (rB == n - 1 && !ANotB.empty()) { break; }

		while (rB < n - 1 && B.count(b[rB + 1])) { rB++; }
		if (A.size() == B.size()) { equalRange[i] = { lB,rB }; }
	}

	int q; cin >> q;
	while (q--) {
		int x, y; cin >> x >> y; x--; y--;
		auto& curR = equalRange[x];
		if (y <= curR.second && y >= curR.first) { cout << "Yes" << '\n'; }
		else { cout << "No" << '\n'; }
	}
}
