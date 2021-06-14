#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
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
		vector<int>a(n);
		for (auto &x : a) { cin >> x; }
		if (a[0] + a[1] <= a.back()) { cout << 1 << " " << 2 << " " << n << '\n'; }
		else { cout << -1 << '\n'; }
	}
}