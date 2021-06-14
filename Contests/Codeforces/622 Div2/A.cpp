#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int a, b, c; cin >> a >> b >> c;
		int res = 0;
		if (a) { res++; a--; }
		if (b) { res++; b--; }
		if (c) { res++; c--; }
		if (b > a) { swap(a, b); }
		if (c > a) { swap(a, c); }
		if (b > c) { swap(b, c); }
		if (a && b) { res++; a--; b--; }
		if (a&&c) { res++; a--; c--; }
		if (b&&c) { res++; b--; c--; }
		if (a&&b&&c) { res++; }

		cout << res << endl;
	}
}