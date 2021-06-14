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
		int a, b; cin >> a >> b;
		if (a > b) { swap(a, b); }
		if (b >= 2 * a) { cout << a << '\n'; }
		else {
			int res = 0, diff = b - a;
			res = diff;
			b -= diff * 2; a -= diff;

			res += 2 * (a / 3); b -= (a / 3) * 3; a -= (a / 3) * 3;
			while (a && b >= 2) {
				res++; a--; b -= 2;
				if (a > b) { swap(a, b); }
			}
			cout << res << '\n';
		}
	}
}