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
		int l, r; cin >> l >> r;
		if (l * 2 > r) { cout << -1 << ' ' << -1 << '\n'; }
		else { cout << l << ' ' << 2 * l << '\n'; }
	}
}