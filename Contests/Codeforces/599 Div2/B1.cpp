#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int k; cin >> k;

	while (k--) {
		int n; cin >> n;
		string s, t; cin >> s >> t;

		int dif = 0; char c1, c2;
		for (int i = 0; i < n; i++) {
			if (s[i] != t[i]) {
				dif++;
				if (dif == 1) { c1 = s[i]; c2 = t[i]; }
				if (dif == 2 && (c1 != s[i] || c2 != t[i])) { dif++; break; }
				if (dif > 2) { break; }
			}
		}
		if (dif != 2) { cout << "NO" << endl; }
		else { cout << "YES" << endl; }
	}
}