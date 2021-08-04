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
		vector<int> freq(26, 0);
		for (auto& c : s) { freq[c - 'a']++; }

		int ans = 0;
		for (auto& x : freq) { ans += min(2, x); }

		cout << ans/2 << '\n';
	}
}