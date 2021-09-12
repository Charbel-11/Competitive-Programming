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
	set<pair<int, int>> here;

	vector<pair<int, int>> pts(n);
	for (auto& p : pts) {
		cin >> p.first >> p.second; 
		here.insert(p);
	}

	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (pts[i].first == pts[j].first || pts[i].second == pts[j].second) { continue; }
			
			if (here.count({ pts[i].first, pts[j].second }) && here.count({ pts[j].first, pts[i].second })) {
				ans++;
			}
		}
	}

	cout << ans / 2 << '\n';
}