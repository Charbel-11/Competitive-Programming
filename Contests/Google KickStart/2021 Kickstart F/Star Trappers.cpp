#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;
typedef long long ll;
const long double eps = 1e-10;

struct pt {
	ll x, y;
	pt(ll xx = 0, ll yy = 0) :x(xx), y(yy) {}
	bool operator == (pt& a) { return (a.x - x == 0) && (a.y - y == 0); }
};

bool operator < (const pt& a, const pt& b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

pt operator-(pt a, pt b) { return pt(a.x - b.x, a.y - b.y); }
ll vec(pt a, pt b) { return a.x * b.y - a.y * b.x; }
ll det(pt a, pt b, pt c) { return vec(b - a, c - a); }

bool right(pt X, pt Y, pt Z) { return (det(X, Y, Z) <= 0); }


long double area(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
	return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

bool isInside(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3, ll x, ll y){
	long double A = area(x1, y1, x2, y2, x3, y3);
	long double A1 = area(x, y, x2, y2, x3, y3);
	long double A2 = area(x1, y1, x, y, x3, y3);
	long double A3 = area(x1, y1, x2, y2, x, y);

	if (A < eps || A1 < eps || A2 < eps || A3 < eps) { return false; }
	return (abs(A - (A1 + A2 + A3)) < eps);
}

long double dist(pt& a, pt& b) {
	long double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n; cin >> n;
		vector<pt> white;
		for (int i = 0; i < n; i++) {
			ll x, y; cin >> x >> y;
			white.push_back(pt(x, y));
		}
		pt blue; cin >> blue.x >> blue.y;

		long double ans = -1;
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				for (int k = j + 1; k < n; k++) {
					if (isInside(white[i].x, white[i].y, white[j].x, white[j].y, white[k].x, white[k].y, blue.x, blue.y)) {
						long double cur = dist(white[i], white[j]) + dist(white[j], white[k]) + dist(white[k], white[i]);
						if (ans < 0) { ans = cur; }
						else { ans = min(ans, cur); }
					}
				}
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (abs(dist(white[i], white[j]) - (dist(white[i], blue) + dist(white[j], blue))) < eps) {
					long double minLeft = -1, minRight = -1;
					for (int k = 0; k < n; k++) {
						if (k == i || k == j) { continue; }
						if (area(white[i].x, white[i].y, white[j].x, white[j].y, white[k].x, white[k].y) < eps) { continue; }
						
						long double cur = dist(white[i], white[k]) + dist(white[j], white[k]);
						if (right(white[k], white[i], white[j])) {
							if (minRight < 0) { minRight = cur; }
							else { minRight = min(minRight, cur); }
						}
						else {
							if (minLeft < 0) { minLeft = cur; }
							else { minLeft = min(minLeft, cur); }
						}
					}

					if (minLeft > 0 && minRight > 0) {
						if (ans < 0) { ans = minLeft + minRight; }
						else { ans = min(ans, minLeft + minRight); }
					}
				}
			}
		}

		cout << "Case #" << qq << ": ";
		if (ans < 0) { cout << "Impossible" << '\n'; }
		else { cout << setprecision(8) << fixed << ans << '\n'; }
	}
}
