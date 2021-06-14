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
		int n, x, m; cin >> n >> x >> m;
		int rL = x, rR = x;
		while (m--) {
			int l, r; cin >> l >> r;
			if (rR<l || rL>r) { continue; }
			rL = min(rL, l); rR = max(rR, r);
		}
		cout << rR - rL + 1 << '\n';
	}
}