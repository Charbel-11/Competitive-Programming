#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

ll digits[9];
int dp[(int)1e3][2];

bool possible(int used, bool odd) {
	if (dp[used][odd] != -1) { return dp[used][odd]; }

	bool cur[9];
	for (int i = 0; i < 9; i++) {
		cur[i] = ((digits[i] - ((used >> i) & 1)) % 2) == 1;
	}
	if (odd) {
		for (int k = 0; k < 9; k++) {
			if (!cur[k]) { continue; }
			for (int l = 0; l < 9; l++) {
				if (l == k || !cur[l]) { continue; }
				for (int m = 0; m < 9; m++) {
					if (m == l || m == k || !cur[m]) { continue; }
					if ((k + l - m) % 11 == 0 || (k + m - l) % 11 == 0 || (l + m - k) % 11 == 0) {
						int nUsed = used;
						nUsed ^= (1 << l); nUsed ^= (1 << k);
						nUsed ^= (1 << m);
						bool poss = possible(nUsed, false);
						if (poss) { return dp[used][odd] = true; }
					}
				}
			}
		}
		for (int i = 0; i < 9; i++) {
			if (!cur[i]) { continue; }
			for (int j = 0; j < 9; j++) {
				if (i == j || digits[j]<2) { continue; }
				if (2 + 2 * j == 1 + i) {
					int nUsed = used;
					nUsed ^= (1 << i);
					bool poss = possible(nUsed, false);
					if (poss) { return dp[used][odd] = true; }
				}
			}
		}
	}
	else {
		for (int k = 0; k < 9; k++) {
			if (!cur[k]) { continue; }
			for (int l = 0; l < 9; l++) {
				if (l == k || !cur[l]) { continue; }
				for (int m = 0; m < 9; m++) {
					if (m == l || m == k || !cur[m]) { continue; }
					for (int n = 0; n < 9; n++) {
						if (n == l || n == m || n == k || !cur[n]) { continue; }
						vector<int> minTemp(4);
						minTemp[0] = k; minTemp[1] = l; minTemp[2] = m; minTemp[3] = n;
						if ((minTemp[0] + minTemp[3] - minTemp[1] - minTemp[2]) % 11 == 0 ||
							(minTemp[0] + minTemp[2] - minTemp[1] - minTemp[3]) % 11 == 0 ||
							(minTemp[0] + minTemp[1] - minTemp[2] - minTemp[3]) % 11 == 0 ||
							(minTemp[2] + minTemp[3] - minTemp[1] - minTemp[0]) % 11 == 0 ||
							(minTemp[1] + minTemp[2] - minTemp[0] - minTemp[3]) % 11 == 0 ||
							(minTemp[1] + minTemp[3] - minTemp[2] - minTemp[0]) % 11 == 0) {
							int nUsed = used;
							nUsed ^= (1 << k); nUsed ^= (1 << l);
							nUsed ^= (1 << m); nUsed ^= (1 << n);
							bool poss = possible(nUsed, false);
							if (poss) { return dp[used][odd] = true; }
						}
					}
				}
			}
		}
	}

	for (int i = 8; i >= 0; i--) {
		if (cur[i]) { return dp[used][odd] = false; }
	}

	return dp[used][odd] = true;
}

int main() {
	int T; cin >> T;

	for (int z = 0; z < T; z++) {
		bool odd = false;
		for (int i = 0; i < 9; i++) {
			cin >> digits[i];
			if (digits[i] % 2) {
				odd = !odd;
			}
		}

		for (int i = 0; i < 1e3; i++) {	dp[i][0] = dp[i][1] = -1;	}

		int used = 0;
		bool b = possible(used, odd);
		cout << "Case #" << z + 1 << ": " << ((b) ? "YES" : "NO") << endl;
	}
}