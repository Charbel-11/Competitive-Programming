#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

typedef long long ll;

struct pt {
	ll x, y;
	pt(ll xx = 0, ll yy = 0) :x(xx), y(yy) {}
	bool operator == (pt &a) { return (a.x - x == 0) && (a.y - y == 0); }
};

bool operator < (const pt &a, const pt &b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

vector<pt> convexhull(vector<pt> ab);
bool PointInConvexPol(vector<pt>& l, pt p);

vector<pt> ch, points;

int main() {
	int t; cin >> t;
	for (int i = 0; i < t; i++) {
		int c, p; cin >> c >> p;
		ch.clear(); ch.resize(c);
		for (auto &x : ch) { cin >> x.x >> x.y; }
		ch = convexhull(ch); ch.push_back(ch.front());
		points.resize(p);
		for (auto &x : points) { cin >> x.x >> x.y; }
		cout << "Case " << i + 1 << endl;
		for (auto &x : ch) { cout << x.x << ' ' << x.y << endl; }
		ch.pop_back();
		for (auto &x : points) {
			string s = (PointInConvexPol(ch, x)) ? "is unsafe!" : "is safe!";
			cout << x.x << ' ' << x.y << ' ' << s << endl;
		}
		if (i + 1 != t) { cout << endl; }
	}
	cin.ignore(2); return 0;
}