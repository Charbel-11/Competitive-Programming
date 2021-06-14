#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int a, b; cin >> a >> b;

		if (a == b && a == 0) { cout << "YES" << endl; continue; }
		if (a <= 1 && b <= 1) { cout << "NO" << endl; continue; }
		if (a > 2 * b || b > 2 * a || (a + b) % 3 != 0) { cout << "NO" << endl; continue; }
		cout << "YES" << endl;
	}
}