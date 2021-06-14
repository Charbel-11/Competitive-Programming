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
		ll a, b, n, m; cin >> a >> b >> n >> m;
		if (n <= max(a, b) && m <= min(a, b)) { cout << "Yes" << '\n'; continue; }
		if (m > min(a, b)) { cout << "No\n"; continue; }
		ll rem = -m + a + b;
		cout << (rem >= n ? "Yes\n" : "No\n");
	}
}