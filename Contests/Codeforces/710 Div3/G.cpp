#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		string s; cin >> s; int n = s.size();
		vector<bool> used(26, 0); vector<int> freq(26, 0);
		for (auto& c : s) { freq[c - 'a']++; }

		string ans = ""; int start = 0;

		while (true) {
			char candidate = 'a';
			int prevS = ans.size();
			for (int i = start; i < n; i++) {
				if (used[s[i] - 'a']) { continue; }
				candidate = max(candidate, s[i]);

				if (freq[s[i] - 'a'] == 1) {
					ans.push_back(candidate); used[candidate - 'a'] = true;

					int j = start;
					for (; j <= i; j++) {
						if (s[j] == candidate) { start = j; break; }
					}
					for (; j < i; j++) { freq[s[j] - 'a']++; }
					break;
				}
				else { freq[s[i] - 'a']--; }
			}
			if (ans.size() == prevS) { break; }
		}

		cout << ans << '\n';
	}
}