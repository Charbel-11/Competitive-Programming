#include <iostream>
#include <string>
#include <map>
#include <set>
#include <climits>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

struct Point {
	ll x, y; Point() {}
	Point(ll _x, ll _y) : x(_x), y(_y) {}
	Point(const Point& rhs) : x(rhs.x), y(rhs.y) {}

	bool operator == (const Point& rhs) const { return x == rhs.x && y == rhs.y; }
	Point operator - (const Point& rhs) const { return Point(x - rhs.x, y - rhs.y); }
	Point operator + (const Point& rhs) const { return Point(x + rhs.x, y + rhs.y); }

	friend istream& operator >> (istream& is, Point& p) { is >> p.x >> p.y; return is; }
};

ll crossProduct(const Point& A, const Point& B) { return A.x * B.y - A.y * B.x; }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n; 
	vector<Point> pts(n);
	for (int i = 0; i < n; i++) { cin >> pts[i]; }

	ll fullArea = 0;
	for (int i = 1; i < n; i++) { fullArea += crossProduct(pts[i - 1], pts[i]); }
	fullArea += crossProduct(pts[n - 1], pts[0]); 

	for (int i = 0; i < n; i++) { pts.push_back(pts[i]); }

	ll ans = LLONG_MAX;
	int l = 0; ll partialArea = 0;
	for (int r = 1; r < 2 * n; r++) {
		partialArea += crossProduct(pts[r - 1], pts[r]);
		ll curArea = partialArea + crossProduct(pts[r], pts[l]);
		ans = min(ans, abs(4 * curArea - fullArea));

		while (4 * curArea > fullArea) {
			partialArea -= crossProduct(pts[l], pts[l + 1]); l++; 
			curArea = partialArea + crossProduct(pts[r], pts[l]);
			ans = min(ans, abs(4 * curArea - fullArea));
		}
	}

	cout << ans << '\n';
}
