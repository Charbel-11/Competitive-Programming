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
		vector<int> p(n); for (auto& xx : p) { cin >> xx; }

		int win = 0;
		for (int i = 1; i <= n; i++) {
			if (i % 2 & p[i - 1]) { win ^= 1; }
		}

		cout << (win ? "first" : "second") << '\n';
	}
}