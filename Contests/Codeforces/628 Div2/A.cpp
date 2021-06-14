#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int x; cin >> x;

		if (x % 2 == 0) { cout << x / 2 << " " << x / 2 << endl; }
		else { cout << x - 1 << " " << 1 << endl; }
	}
}