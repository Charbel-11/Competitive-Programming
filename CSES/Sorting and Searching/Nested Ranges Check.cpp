#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

struct range {
	int l, r, id;
	range(int _l, int _r, int _id) :l(_l), r(_r), id(_id) {}

	bool operator<(range& rhs) {
		if (l == rhs.l) { return r > rhs.r; }
		return l < rhs.l;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<range> ranges;
	for (int i = 0; i < n; i++) {
		int l, r; cin >> l >> r;
		ranges.push_back(range(l, r, i));
	}
	sort(ranges.begin(), ranges.end());

	vector<int> ans1(n, 0), ans2(n, 0);
	int maxR = 0;
	for (int i = 0; i < n; i++) {
		if (maxR >= ranges[i].r) { ans2[ranges[i].id] = 1; }
		else { maxR = ranges[i].r; }
	}
	
	int minR = 1e9 + 5;
	for (int i = n - 1; i >= 0; i--) {
		if (minR <= ranges[i].r) { ans1[ranges[i].id] = 1; }
		else { minR = ranges[i].r; }
	}

	for (auto& x : ans1) { cout << x << ' '; } cout << '\n';
	for (auto& x : ans2) { cout << x << ' '; }cout << '\n';
}