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

		int ans = 0; 
		bool allOne = true, even = true;
		for (int i = 0; i < n; i++) {
			int cur; cin >> cur;
			if (cur != 1) { allOne = false; }
			ans ^= cur; even = !even;
		}

		if (allOne) {
			cout << (even ? "First" : "Second") << '\n';
		}
		else {
			cout << (ans ? "First" : "Second") << '\n';
		}
	}
}