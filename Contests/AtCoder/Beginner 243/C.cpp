#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

struct pt {
	int x, y; bool r; pt() {}
	pt(int _x, int _y, bool _r) :x(_x), y(_y), r(_r) {}

	bool operator < (const pt& rhs) {
		return y < rhs.y;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<pt> pts(n);
	for (int i = 0; i < n; i++) {
		cin >> pts[i].x >> pts[i].y;
	}
	string s; cin >> s;
	for (int i = 0; i < n; i++) {
		pts[i].r = s[i] == 'R';
	}

	sort(pts.begin(), pts.end());

	bool coll = false;
	int rightOf = 1e9 + 5, leftOf = -1, curY = -1;
	for (int i = 0; i < n; i++) {
		if (pts[i].y != curY) {
			curY = pts[i].y;
			rightOf = 1e9 + 5;
			leftOf = -1;
		}

		if (pts[i].r) { rightOf = min(rightOf, pts[i].x); }
		else { leftOf = max(leftOf, pts[i].x); }

		if (rightOf <= leftOf) { coll = true; break; }
	}

	cout << (coll ? "Yes" : "No") << '\n';
}