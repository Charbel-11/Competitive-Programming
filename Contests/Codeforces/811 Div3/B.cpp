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
		vector<int> a(n); for (auto& x : a) { cin >> x; } 

		int ans = n; set<int> seen;
		for (int i = n - 1; i >= 0; i--) {
			if (seen.count(a[i])) { break; }
			ans--; seen.insert(a[i]);
		}

		cout << ans << '\n';
	}
}
