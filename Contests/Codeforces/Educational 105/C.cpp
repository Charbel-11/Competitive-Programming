#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int curScore(vector<int>& spec, int low, int hi) {
	int id1 = lower_bound(spec.begin(), spec.end(), low) - spec.begin();
	int id2 = upper_bound(spec.begin(), spec.end(), hi) - spec.begin() - 1;

	return id2 - id1 + 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n, m; cin >> n >> m;
		vector<int> a(n), b(m);
		for (auto& x : a) { cin >> x; }
		for (auto& x : b) { cin >> x; }

		int ans = 0;
		vector<pair<int, bool>> point;
		for (int i = 0; i < n; i++) {
			if (a[i] > 0) { point.push_back({ a[i], 0 }); }
		}
		for (int i = 0; i < m; i++) {
			if (b[i] > 0) { point.push_back({ b[i], 1 }); }
		}
		sort(point.begin(), point.end());

		vector<int> bonus(point.size() + 1, 0);
		for (int i = 0; i + 1 < point.size(); i++) {
			if (point[i].first == point[i + 1].first)
				bonus[i]++;
		}
		for (int i = (int)bonus.size() - 2; i >= 0; i--) { bonus[i] += bonus[i + 1]; }

		int curAns = 0;
		int low = 0, hi = 0, boxes = 0;
		for (int i = 0; i < point.size(); i++) {
			if (!point[i].second) { boxes++; }
			hi = point[i].first;
			low = point[i].first - boxes;

			curAns = max(curAns, curScore(b, low + 1, hi) + bonus[i + 1]);
		}
		ans += curAns;

		point = vector<pair<int, bool>>();
		for (int i = 0; i < n; i++) {
			if (a[i] < 0) { point.push_back({ -a[i], 0 }); }
		}
		for (int i = 0; i < m; i++) {
			if (b[i] < 0) { point.push_back({ -b[i], 1 }); }
		}
		sort(point.begin(), point.end());

		bonus.clear(); bonus.resize(point.size() + 1, 0);
		for (int i = 0; i + 1 < point.size(); i++) {
			if (point[i].first == point[i + 1].first)
				bonus[i]++;
		}
		for (int i = (int)bonus.size() - 2; i >= 0; i--) { bonus[i] += bonus[i + 1]; }

		curAns = boxes = 0;
		low = hi = 0;
		for (int i = 0; i < point.size(); i++) {
			if (!point[i].second) { boxes++; }
			hi = point[i].first;
			low = point[i].first - boxes;

			curAns = max(curAns, curScore(b, -hi, -(low + 1)) + bonus[i + 1]);
		}
		ans += curAns;

		cout << ans << '\n';
	}
}