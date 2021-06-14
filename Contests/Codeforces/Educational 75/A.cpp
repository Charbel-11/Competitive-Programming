#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		string s, res= ""; cin >> s;
		if (s.size() == 1) { cout << s << endl; continue; }
		set<char> used;
		for (int i = 0; i < s.size() - 1; i++) {
			if (s[i] != s[i + 1] && s[i] != '.') { used.insert(s[i]); }
			else if (s[i]!='.') { s[i+1] = '.'; }
		}
		if (s[s.size()-1] != s[s.size() - 2] && s[s.size()-1] != '.') { used.insert(s[s.size() - 1]); }

		for (auto x : used) { res.push_back(x); }
		cout << res << endl;
	}
}