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
		int n, m; cin >> n >> m;
		vector<int> dpR(n * m, 0), dpC(n * m, 0);
		vector<bool> coveredCol(m, 0); int colSum = 0;

		string s; cin >> s;
		int lastM = 0;
		for (int i = 0; i < m; i++) {
			if (s[i] == '1') {
				lastM++; colSum++;
				coveredCol[i] = true;
			}

			dpR[i] = (lastM > 0);
			dpC[i] = colSum;
		}

		for (int i = m; i < m * n; i++) {
			lastM -= (s[i - m] == '1');
			lastM += (s[i] == '1');
			dpR[i] = dpR[i - m] + (lastM > 0);

			if (s[i] == '1' && !coveredCol[(i % m)]) {
				coveredCol[i % m] = true;
				colSum++;
			}
			dpC[i] = colSum;
		}

		for (int i = 0; i < n * m; i++) {
			cout << dpR[i] + dpC[i] << ' ';
		}
		cout << '\n';
	}
}