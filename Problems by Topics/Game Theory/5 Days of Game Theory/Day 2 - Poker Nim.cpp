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
		int n, k; cin >> n >> k;

		int ans = 0;
		for (int i = 0; i < n; i++) {
			int cur; cin >> cur;
			ans ^= cur;
		}

		cout << (ans ? "First" : "Second") << '\n';
	}
}