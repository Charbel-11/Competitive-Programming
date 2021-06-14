#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ll u, v; cin >> u >> v;

	if (u > v) { cout << -1 << endl; return 0; }
	if (u == 0 && v == 0) { cout << 0 << endl; return 0; }
	if (u == v) { cout << 1 << endl; cout << u << endl; return 0; }
	if (u == 0 && (v % 2 == 0)) { cout << 2 << endl; cout << v / 2ll << " " << v / 2ll << endl; return 0; }
	
	ll firstNum = u, otherNum = 0;
	ll needed = v - u;
	bool OK = true;
	for (int i = 1; i < 64; i++) {
		bool one = (needed >> i) & 1;
		if (!one) { continue; }
		if (one && ((u >> (i - 1)) & 1ll)) { OK = false; break; }

		firstNum |= (1ll << (i - 1));
		otherNum |= (1ll << (i - 1));
	}
	if (OK && ((firstNum^otherNum)==u) && firstNum+otherNum==v) {
		cout << 2 << endl;
		cout << firstNum << " " << otherNum << endl;
		return 0;
	}
	
	if ((v - u) % 2 == 0) {
		cout << 3 << endl;
		cout << u << " ";
		v -= u;
		cout << (v / 2ll) << " " << (v / 2ll) << endl;
		return 0;
	}

	cout << -1 << endl;
}