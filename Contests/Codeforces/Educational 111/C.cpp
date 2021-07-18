#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int dist(pair<int, int>& p1, pair<int, int>& p2) {
	return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

bool isGood(vector<pair<int, int>>& v) {
	int n = v.size();
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			for (int k = j + 1; k < n; k++) {
				if (dist(v[i], v[j]) == dist(v[i], v[k]) + dist(v[j], v[k])) { return false; }
				if (dist(v[i], v[k]) == dist(v[i], v[j]) + dist(v[j], v[k])) { return false; }
				if (dist(v[j], v[k]) == dist(v[i], v[k]) + dist(v[i], v[j])) { return false; }
			}
		}
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<int> a(n); for (auto& x : a) { cin >> x; }
		
		int ans = 0;
		for (int l = 0; l < n; l++) {
			vector<pair<int, int>> cur;
			cur.push_back({ a[l], l + 1 }); ans++;
			for (int r = l + 1; r < min(l + 4, n); r++) {
				cur.push_back({ a[r], r + 1 });
				if (isGood(cur)) { ans++; }
				else { break; }
			}
		}
		
		cout << ans << '\n';
	}
}