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
		int n; cin >> n;
		string s; cin >> s;
		s.erase(unique(s.begin(), s.end()), s.end());
		set<char> seen;

		bool OK = true;
		for (auto& c : s) {
			if (seen.count(c)) { OK = false; break; }
			seen.insert(c);
		}

		cout << (OK ? "YES" : "NO") << '\n';
	}
}
