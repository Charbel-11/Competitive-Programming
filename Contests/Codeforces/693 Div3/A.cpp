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
		ll w, h, n; cin >> w >> h >> n;
		ll ans = 1;
		while (w % 2 == 0) { ans <<= 1; w >>= 1; if (ans > n) { break; } }
		while (h % 2 == 0) { ans <<= 1; h >>= 1; if (ans > n) { break; } }
		cout << (ans >= n ? "YES" : "NO") << '\n';
	}
}