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
		ll a, b, n; cin >> a >> b >> n;
		int ans = 0;
		if (a < b) { swap(a, b); }
		while (a <= n) {
			b += a; ans++;
			swap(a, b);
		}
		cout << ans << '\n';
	}
}