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
		string s; cin >> s;
		int ans = 0;
		vector<bool> changed(s.size(), 0);
		for (int i = 1; i < s.size(); i++) {
			if (changed[i]) { continue; }
			if (i >= 2  && !changed[i - 2] && s[i] == s[i - 2]) {
				ans++; changed[i] = true; 
				continue;
			}
			if (changed[i - 1]) { continue; }
			if (s[i] == s[i - 1]) {
				ans++; changed[i] = true;
				continue;
			}
			else if (i < s.size() && s[i - 1] == s[i + 1]) {
				changed[i + 1] = true; ans++; 
				continue;
			}
		}
		cout << ans << '\n';
	}
}