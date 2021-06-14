#include <iostream>
#include <cmath>
#include <algorithm>
#include <string.h>
#include <cstdio>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <climits>
using namespace std;

typedef long long ll;
int INF = INT_MAX;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int t; cin >> t;

	while (t--) {
		int n, m, a, b; cin >> n >> m >> a >> b;
		if (n*a != b * m) { cout << "NO" << '\n'; continue; }
		cout << "YES" << endl;

		vector<vector<bool>> ans(n, vector<bool>(m, 0));
		int idx = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < a; j++) {
				ans[i][idx] = 1;
				idx++; idx %= m;
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << ans[i][j];
			}
			cout << endl;
		}
	}
}