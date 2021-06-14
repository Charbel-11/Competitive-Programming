#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;
	for (int z = 0; z < t; z++) {
		int b, p, f; cin >> b >> p >> f;
		int h, c; cin >> h >> c;

		int res = 0;
		if (h > c) {
			res += h * min(b / 2, p);
			b -= min(b / 2, p) * 2;
			res += c * min(b / 2, f);
		}
		else {
			res += c * min(b / 2, f);
			b -= min(b / 2, f) * 2;
			res += h * min(b / 2, p);
		}
		cout << res << endl;
	}
}
