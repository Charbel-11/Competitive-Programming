#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int k; cin >> k;

	double res[8][8]; int choices[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			res[i][j] = 1.0;
			choices[i][j] = (i > 0) + (i < 7) + (j > 0) + (j < 7);
		}
	}

	int dx[] = { 1,-1,0,0 }, dy[] = { 0,0,1,-1 };

	for (int i1 = 0; i1 < 8; i1++) {
		for (int j1 = 0; j1 < 8; j1++) {
			double cur[8][8], prev[8][8];
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					cur[i][j] = prev[i][j] = 0;
			prev[i1][j1] = 1;

			for (int kk = 1; kk <= k; kk++) {
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						cur[i][j] = 0;
						for (int it = 0; it < 4; it++) {
							int ni = i + dx[it], nj = j + dy[it];
							if (!(ni >= 0 && nj >= 0 && ni < 8 && nj < 8)) { continue; }
							cur[i][j] += prev[ni][nj] * (1.0 / choices[ni][nj]);
						}
					}
				}
				swap(cur, prev);
			}

			swap(cur, prev);
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					res[i][j] *= (1 - cur[i][j]);
		}
	}

	double ans = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			ans += res[i][j];
	cout << fixed << setprecision(6) << ans << '\n';
}