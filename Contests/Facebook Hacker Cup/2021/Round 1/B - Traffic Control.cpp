#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("in.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n, m, A, B; ifs >> n >> m >> A >> B;
		ofs << "Case #" << qq << ": ";

		int neededA = A - (n + m - 2), neededB = B - (n + m - 2);
		if (neededA <= 0 || neededB <= 0) { ofs << "Impossible\n"; }
		else {
			ofs << "Possible\n";

			vector<vector<int>> ans(n, vector<int>(m, 1000));
			for (int i = 0; i < n; i++) { ans[i][0] = ans[i][m-1] = 1; }
			for (int j = 0; j < m; j++) { ans[n - 1][j] = 1; }

			ans[0][0] = neededA; ans[0][m - 1] = neededB;

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					ofs << ans[i][j] << ' ';
				}
				ofs << '\n';
			}
		}	
	}
}