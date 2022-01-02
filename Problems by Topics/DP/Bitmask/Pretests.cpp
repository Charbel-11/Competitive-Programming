// https://codeforces.com/gym/102006/problem/F

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <bitset>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

//	freopen("tests.in", "r", stdin);

	int P; cin >> P;
	while (P--) {
		int t, n; cin >> t >> n;
		
		vector<int> notCovered(1 << t, 0);
		for (int i = 0; i < n; i++) {
			string cur; cin >> cur;
			int num = 0;
			for (int i = 0; i < t; i++) {
				if (cur[i] == '1') { num |= (1 << i); }
			}
			notCovered[num]++;
		}

		for (int k = 0; k < t; k++) {
			for (int mask = 0; mask < (1 << t); mask++) {
				if (!((1 << k) & mask)) { notCovered[mask] += notCovered[mask ^ (1 << k)]; }
			}
		}

		vector<int> minCost(1 << t, 1e7), firstUsed(1 << t, -1);
		minCost[(1 << t) - 1] = 0;
		for (int m = (1 << t) - 2; m >= 0; m--) {
			for (int k = 0; k < t; k++) {
				if ((1 << k) & m) { continue; }
				int nxtMask = m ^ (1 << k);
				if (minCost[nxtMask] < minCost[m]) {
					minCost[m] = minCost[nxtMask];
					firstUsed[m] = k;
				}
			}
			minCost[m] += notCovered[m];
		}

		int curM = 0;
		cout << minCost[curM] << '\n';
		while (curM != (1 << t) - 1) {
			int curT = firstUsed[curM];
			curM ^= (1 << curT);
			cout << curT + 1 << ' ';
		}
		cout << '\n';
	}
}