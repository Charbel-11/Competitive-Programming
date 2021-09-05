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
		string ans = "";

		for (auto& c : s) {
			if (c == 'U') { ans.push_back('D'); }
			else if (c == 'D') { ans.push_back('U'); }
			else { ans.push_back(c); }
		}

		cout << ans << '\n';
	}
}