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

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<int> x(n); for (auto& xx : x) { cin >> xx; }
		int ans = 0; set<int> used;
		for (int i = 0; i < n; i++) {
			if (used.count(x[i])) { x[i]++; }
			if (used.count(x[i])) { continue; }
			ans++; used.insert(x[i]);
		}
		cout << ans << '\n';
	}
}