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
		int ans = n - 1, d = 2;
		while (d*d <= n) {
			ans = min(ans, d - 1 + ((n-1)/d));
			d++;
		}
		cout << ans << '\n';
	}
}