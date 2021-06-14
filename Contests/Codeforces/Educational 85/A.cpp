#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		int p = 0, c = 0; bool OK = true;
		while (n--) {
			int curP, curC; cin >> curP >> curC;
			if (p > curP || c > curC) { OK = false; continue; }
			if (curP < curC) { OK = false; continue; }
			if (curP - p < curC - c) { OK = false; continue; }
			p = curP; c = curC;
		}
		cout << (OK ? "YES" : "NO") << endl;
	}
}