#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int T; cin >> T;

	while (T--) {
		int n, d; cin >> n >> d;
		if (n >= d) { cout << "YES" << endl; continue; }
		int x = d/n;
		
		bool OK = false;
		int res = x + ((d + x) / (x + 1));
		while (x < n) {
			if (res <= n) { OK = true; break; }
			x++; res = x + ((d + x) / (x + 1));
		}

		if (OK) { cout << "YES" << endl; }
		else { cout << "NO" << endl; }
	}
}