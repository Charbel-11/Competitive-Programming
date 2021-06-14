#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

struct circle { int x, y, r; circle() {} };
vector<circle> c; multiset<int> yCoord[10001];

int main() {
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		yCoord[x].insert(y);
	}
	int m; cin >> m; while (m--) {
		int x, y, r; cin >> x >> y >> r;
		for (int i = max(0, x - r); i <= min(10000, x + r); i++) {
			int dy = r * r - (x - i) * (x - i);
			dy = (int)floor(sqrt(dy));
			int l = y - dy, r = y + dy;
			auto it1 = yCoord[i].lower_bound(l), it2 = yCoord[i].upper_bound(r);
			yCoord[i].erase(it1, it2);
		}
	}
	int res = 0; for (int i = 0; i <= 10000; i++) res += yCoord[i].size();
	cout << res << '\n'; cin.ignore(2); return 0;
}