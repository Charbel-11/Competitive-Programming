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
		string s, t; cin >> s >> t;
		if (t == "a") { cout << 1 << '\n'; continue; }

		bool hasA = false;
		for (auto& c : t) {
			if (c == 'a') { hasA = true; }
		}

		if (hasA) { cout << -1 << '\n'; continue; }
		int n = s.size();
		cout << (1ll << n) << '\n';
	}
}