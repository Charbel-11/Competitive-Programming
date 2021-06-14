#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;
typedef long double ld;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int T; cin >> T;
	for (int q = 1; q <= T; q++) {
		int w, h, l, u, r, d; cin >> w >> h >> l >> u >> r >> d;
		l--; u--; r--; d--;
		vector<vector<ld>> prob(h,vector<ld>(w, 1));	//h rows, w columns

		ld bad = 0;
		for(int i = 0; i < h; i++){
			for (int j = 0; j < w; j++) {
				if (i == 0 && j == 0) { continue; }

				prob[i][j] = (j != w - 1 ? 0.5 : 1)*(i ? prob[i - 1][j] : 0) + (i != h - 1 ? 0.5 : 1)*(j ? prob[i][j - 1] : 0);
				if (j >= l && j <= r && i == u) {
					if (j!=l){
						prob[i][j] = (j != w - 1 ? 0.5 : 1)*(i ? prob[i - 1][j] : 0);
					}
					bad += prob[i][j];
				}
				else if (j == l && i >= u && i <= d) {
					if (i != u){
						prob[i][j] = (i != h - 1 ? 0.5 : 1)*(j ? prob[i][j - 1] : 0);
					}
					bad += prob[i][j];
				}
			}
		}

		cout << "Case #" << q << ": " << setprecision(6) << fixed << 1.0 - bad << endl;
	}
}