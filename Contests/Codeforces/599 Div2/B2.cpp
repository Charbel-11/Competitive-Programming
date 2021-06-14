#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int k; cin >> k;

	while (k--) {
		int n; cin >> n;
		string s, t; cin >> s >> t;
		map<char, int> freq;
		for (int i = 0; i < n; i++) {
			freq[s[i] - 'a']++;
			freq[t[i] - 'a']++;
		}
		bool OK = true;
		for (auto &x : freq) {
			if (x.second % 2) {
				OK = false; break;
			}
		}
		if (!OK) { cout << "NO" << endl; continue; }

		vector<pair<int, int>> res;
		for (int i = 0; i < n; i++) {
			if (s[i] != t[i]) {
				bool found = false;
				for (int j = i + 1; j < n; j++) {
					if (t[i] == t[j]) {
						found = true;
						res.push_back({ i + 1, j + 1 });
						swap(s[i], t[j]); break;
					}
				}
				if (!found) {
					for (int j = i + 1; j < n; j++) {
						if (t[i] == s[j]) {
							res.push_back({ j + 1, i + 2 });
							swap(s[j], t[i + 1]);
							res.push_back({ i + 1, i + 2 });
							swap(s[i], t[i + 1]);
							break;
						}
					}
				}
			}
		}
		cout << "YES" << endl;
		cout << res.size() << endl;
		for (auto &x : res) { cout << x.first << " " << x.second << endl; }
	}
}