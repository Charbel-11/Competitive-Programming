#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

typedef long long ll;

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

vector<pt> convexhull(vector<pt>& ab) {
	sort(ab.begin(), ab.end());
	ab.erase(unique(ab.begin(), ab.end()), ab.end());
	int l = (int)ab.size(), i, j = 0, k;
	vector<pt> res(l + 1); if (l < 3) { return ab; }

	for (i = 0; i < l; i++) {
		while (j - 2 >= 0 && right(res[j - 2], res[j - 1], ab[i])) { j--; }
		res[j++] = ab[i];
	}
	k = j;
	for (i = l - 2; i >= 0; i--) {
		while (j - 1 >= k && right(res[j - 2], res[j - 1], ab[i])) { j--; }
		res[j++] = ab[i];
	}
	if (res[j - 1] == res[0]) { j--; }
	return vector<pt>(res.begin(), res.begin() + j);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n; cin >> n;
	vector<pt> pts;
	for (int i = 0; i < n; i++) {
		ll x, y; cin >> x >> y;
		pts.push_back(pt(x, y));
	}
	vector<pt> ans = convexhull(pts);
	cout << ans.size() << '\n';
	for (auto& p : ans) { cout << p.x << " " << p.y << '\n'; }
}