#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;
typedef long double ld;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("in2.txt");

	int T; ifs >> T;
	for (int q = 1; q <= T; q++) {
		int u; ifs >> u;

		vector<vector<int>> freq(10, vector<int>(26, 0));
		for (int tt = 0; tt < 10000; tt++) {
			int M; ifs >> M;
			string r; ifs >> r;
		}


		for (int tt = 0; tt < 10000; tt++) {
			int M; ifs >> M;
			string r; ifs >> r;

			vector<vector<ld>> probR(10, vector<ld>(26, 0));

			for (int j = r.size() - 1; j >= 0; j--) {
				int curC = r[j] - 'A';

				for (int i = 0; i < 10; i++) {
					ld curProb = 0;
					if (i == 0 && j == 0) { curProb = 0; }
					else if (i == 0 && j != r.size() - 1) {
						ll ways = 1, total = 10;
						ways *= 9; total *= 10;
						curProb = (ld)ways / total;
					}
					else { curProb = 1.0 / 10.0; }
					probR[i][curC] += curProb;
				}
			}

			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 26; j++) {
					if (probR[i][j] == 0) { continue; }
					probR[i][j] /= 1e4;
					prob[i][j] += probR[i][j];
				}
		}

		vector<bool> used(26, 0);

		cout << "Case #" << q << ": ";
		for (int i = 0; i < 10; i++) {
			char cur = 'A'; ld maxP = 0;
			for (int j = 0; j < 26; j++) {
				if (used[j]) { continue; }
				if (prob[i][j] - maxP > -0.00001) {
					maxP = prob[i][j];
					cur = 'A' + j;
				}
			}
			used[cur - 'A'] = 1;
			cout << cur;
		}
		cout << endl;
	}
}