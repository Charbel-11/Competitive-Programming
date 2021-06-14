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

	int n, q; cin >> n >> q;
	int ones = 0, zeros = 0;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		int cur; cin >> cur; a[i] = cur;
		if (cur) { ones++; }
		else { zeros++; }
	}

	while (q--) {
		int t; cin >> t;
		if (t == 1) {
			int x; cin >> x; x--;
			if (a[x] == 1) { a[x] = 0; ones--; zeros++; }
			else { a[x] = 1; ones++; zeros--; }
		}
		else {
			int k; cin >> k;
			if (ones >= k) { cout << 1 << '\n'; }
			else { cout << 0 << '\n'; }
		}
	}
}