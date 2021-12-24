#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

bool dp[101];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	for (int i = 1; i < 101; i++) {
		for (int x : {2, 3, 5}) {
			if (i - x >= 0 && !dp[i - x]) { dp[i] = true; break; }
		}
	}

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		cout << (dp[n] ? "First" : "Second") << '\n';
	}
}