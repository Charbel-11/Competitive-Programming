#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int T; cin >> T;

	while (T--) {
		string s; cin >> s;
		set<char> used;
		vector<char> chars(26, '@');

		bool possible = true; int cur = 0; 
		chars[0] = s[0]; used.insert(s[0]);
		for (int i = 1; i < s.size(); i++) {
			if (cur == 0) {
				if (chars[cur + 1] == s[i]) { cur++; continue; }
				if (used.count(s[i])) { possible = false; break; }
				if (chars[cur + 1] == '@') { chars[++cur] = s[i]; }
				else { chars.insert(chars.begin(), s[i]); }
				used.insert(s[i]);
				continue;
			}
			if (cur == 25) {
				if (chars[cur - 1] == s[i]) { cur--; continue; }
				if (chars[cur - 1] != '@' || used.count(s[i])) { possible = false; break; }
				chars[--cur] = s[i]; used.insert(s[i]);
				continue;
			}
			if (chars[cur - 1] == s[i]) { cur--; continue; }
			if (chars[cur + 1] == s[i]) { cur++; continue; }
			if (used.count(s[i]) || chars[cur+1] != '@') { possible = false; continue; }

			chars[++cur] = s[i]; used.insert(s[i]);
		}

		if (!possible) { cout << "NO" << endl; continue; }

		vector<char> rem;
		for (int i = 0; i < 26; i++) {
			if (!used.count('a' + i)) { rem.push_back('a' + i); }
		}
		for (int i = 0; i < 26; i++) {
			if (chars[i] == '@') { chars[i] = rem.back(); rem.pop_back(); }
		}

		cout << "YES" << endl;
		for (auto &x : chars) { if (x!='@')cout << x; }cout << endl;
	}
}