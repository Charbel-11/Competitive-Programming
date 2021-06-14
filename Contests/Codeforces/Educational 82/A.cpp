#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		string s; cin >> s;
		while (!s.empty() && s.back() == '0') { s.pop_back(); }
		if (s.empty()) { cout << 0 << endl; continue; }

		int i = 0, ans = 0;
		while (i < s.size() && s[i] == '0') { i++; }
		for (int l = i; l < s.size(); l++) {
			if (s[l] == '0') { ans++; }
		}

		cout << ans << endl;
	}
}