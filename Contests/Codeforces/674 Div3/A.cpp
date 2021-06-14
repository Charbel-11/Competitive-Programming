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
		int n, x; cin >> n >> x;
		int ans = 1;
		if (n > 2) {
			n -= 2; ans += (n + x - 1) / x;
		}
		cout << ans << '\n';
	}
}