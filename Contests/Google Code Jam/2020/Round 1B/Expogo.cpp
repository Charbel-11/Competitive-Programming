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

	int T; cin >> T;
	for (int q = 1; q <= T; q++) {
		ll X, Y; cin >> X >> Y;
		ll aX = abs(X), aY = abs(Y);

		vector<int> bitsX(34, 0), bitsY(34, 0);
		for (int i = 0; i < 33; i++) {
			if ((aX >> i) & 1) { bitsX[i] = 1; }
			if ((aY >> i) & 1) { bitsY[i] = 1; }
		}

		string ans = ""; bool OK = true;

		for (int i = 32; i >= 0; i--) {
			if (bitsX[i] == 0 && bitsY[i] == 0) { continue; }
			if (bitsX[i] != bitsY[i]) { continue; }
			int start = i;
			while (i >= 0 && bitsX[i] == bitsY[i] && bitsX[i] == 1) {
				i--;
			}
			if (i < 0) { OK = false; break; }
			if (bitsX[i] == 1) {
				bitsX[i] = -1;
				int j = i + 1;
				while (bitsX[j] == 1) { bitsX[j] = 0; j++; }
				bitsX[j]++;
			}
			if (bitsY[i] == 1) {
				bitsY[i] = -1;
				int j = i + 1;
				while (bitsY[j] == 1) { bitsY[j] = 0; j++; }
				bitsY[j]++;
			}
		}

		int last1 = 0;
		for (int i = 32; i >= 0; i--) {
			if (bitsX[i] || bitsY[i]) { last1 = i; break; }
		}
		for (int i = last1; i >= 0; i--) {
			if (bitsX[i] == 0 && bitsY[i] == 0) {
				int start = i;
				while (i >= 0 && bitsX[i] == bitsY[i] && bitsX[i] == 0) { i--; }
				if (i < 0) { OK = false; break; }
				if (bitsX[i] == 1) {
					bitsX[start] = 1;
					for (int j = start - 1; j >= i; j--) {
						bitsX[j] = -1;
					}
				}
				else if (bitsX[i] == -1) {
					bitsX[start] = -1;
					for (int j = start - 1; j >= i; j--) {
						bitsX[j] = 1;
					}
				}

				if (bitsY[i] == 1) {
					bitsY[start] = 1;
					for (int j = start - 1; j >= i; j--) {
						bitsY[j] = -1;
					}
				}
				else if (bitsY[i] == -1) {
					bitsY[start] = -1;
					for (int j = start - 1; j >= i; j--) {
						bitsY[j] = 1;
					}
				}
			}
		}

		bool noOne = false;
		for (int i = 0; i < 31; i++) {
			if (abs(bitsX[i]) >= 2 || abs(bitsY[i]) >= 2) { OK = false; break; }
			if (bitsX[i] == 0 && bitsY[i] == 0) { noOne = true; continue; }
			if ((bitsX[i] || bitsY[i]) && noOne) { OK = false; break; }
			if (bitsX[i] == bitsY[i]) { OK = false; break; }
		}

		cout << "Case #" << q << ": ";
		if (!OK) { cout << "IMPOSSIBLE" << endl; continue; }

		for (int i = 0; i < 31; i++) {
			if (bitsX[i] == 1) {
				if (X > 0) { ans.push_back('E'); }
				else { ans.push_back('W'); }
			}
			else if (bitsX[i] == -1) {
				if (X > 0) { ans.push_back('W'); }
				else { ans.push_back('E'); }
			}
			if (bitsY[i] == 1) {
				if (Y > 0) { ans.push_back('N'); }
				else { ans.push_back('S'); }
			}
			else if (bitsY[i] == -1) {
				if (Y > 0) { ans.push_back('S'); }
				else { ans.push_back('N'); }
			}
		}

		cout << ans << endl;
	}
}