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

int test(int c, int h, int o) {
	while (c >= 6 && h >= 12 && o >= 6 && (h >= 2 * o || h >= 2 * c)) {
		c -= 6; h -= 12; o -= 6;
	}
	while (c >= 1 && o >= 2 && o >= 2*c) {
		c -= 1; o -= 2;
	}
	while (h >= 2 && o >= 1) {
		h -= 2; o -= 1;
	}
	int ans = c + h + o;

	if (h > 0) {
		int c2 = h % 2 + (h+1) / 2 - o;
		ans = min(ans, c2 + c);
	}
	if (o > 0) {
		int c2 = 2 * o - h + c;
		ans = min(ans, c2);
		int c3 = o % 2 + max((o + 1) / 2 - c, 0);
		int remC = c - (o + 1) / 2;
		ans = min(ans, c3 + h + max(remC, 0));
	}
	if (c > 0) {
		int c2 = 2 * c - o;
		ans = min(ans, c2 + h);
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int c, h, o; cin >> c >> h >> o;

		cout << test(c, h, o) << '\n';
	}
}