#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int a, b, c, d; cin >> a >> b >> c >> d;
		int x, y, x1, y1, x2, y2; cin >> x >> y >> x1 >> y1 >> x2 >> y2;

		if (x == x1 && x == x2 && y == y1 && y == y2) {
			if (a + b + c + d == 0) { cout << "Yes" << endl; }
			else { cout << "No" << endl; }
			continue;
		}
		if (x == x1 && x == x2) {
			if (a + b > 0) { cout << "No" << endl; continue; }
		}
		if (y == y1 && y == y2) {
			if (c + d > 0) { cout << "No" << endl; continue; }
		}

		bool OK = true;
		if (a > b) {
			if (x - x1 < a - b) { OK = false; }
		}
		else {
			if (x2 - x < b - a) { OK = false; }
		}
		if (c > d) {
			if (y - y1 < c - d) { OK = false; }
		}
		else {
			if (y2 - y < d - c) { OK = false; }
		}

		cout << (OK ? "Yes" : "No") << endl;
	}
}