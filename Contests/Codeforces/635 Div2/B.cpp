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
		int x, n, m; cin >> x >> n >> m;
		while (x > 0 && (n || m)) {
			if (n && (x / 2 + 10) < x) {
				x = x / 2 + 10; n--;
			}
			else if (!m) { break; }
			else {
				x -= 10; m--;
			}
		}
		cout << (x>0 ? "NO" : "YES") << endl;
	}
}