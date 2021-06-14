#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		string s; cin >> s;

		while (!s.empty() && (s.back() - '0') % 2 == 0) { s.pop_back(); }
		if (s.empty()) { cout << -1 << endl; continue; }

		int curSum = 0, oddIdx = -1;
		for (int i = 0; i < s.size(); i++) {
			curSum += s[i] - '0';
			if ((s[i] - '0') % 2 && oddIdx == -1) { oddIdx = i; }
		}

		if (curSum % 2 == 0) { cout << s << endl; }
		else if (oddIdx == s.size() - 1) { cout << -1 << endl; }
		else {
			if (oddIdx == 0 && s.size() > 1 && s[1] == '0') {
				int skip = 0;
				while (skip < s.size() - 1 && s[skip + 1] == '0') { skip++; } 

				for (int i = skip + 1; i < s.size(); i++) {
					cout << s[i];
				}cout << endl; continue;
			}

			for (int i = 0; i < s.size(); i++) {
				if (i != oddIdx) { cout << s[i]; }
			}
			cout << endl;
		}
	}
}