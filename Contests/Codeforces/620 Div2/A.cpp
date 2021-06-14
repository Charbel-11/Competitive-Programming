#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int x, y, a, b; cin >> x >> y >> a >> b;
		y -= x; x = 0;

		if ( y % (a + b) == 0) { cout << y / (a + b) << endl; }
		else { cout << -1 << endl; }
	}
}