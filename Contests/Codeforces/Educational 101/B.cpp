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
		vector<int> r(n); for (auto& x : r) { cin >> x; }
		int m; cin >> m;
		vector<int> b(m); for (auto& x : b) { cin >> x; }

		int maxR = max(0, r[0]), maxB = max(0, b[0]);
		for (int i = 1; i < n; i++) { r[i] += r[i - 1]; maxR = max(maxR, r[i]); }
		for (int i = 1; i < m; i++) { b[i] += b[i - 1]; maxB = max(maxB, b[i]); }

		cout << maxR + maxB << '\n';
	}
}