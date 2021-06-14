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

	ifstream ifs("input.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;

	for (int qq = 1; qq <= t; qq++) {
		int n; ifs >> n;
		string I, O; ifs >> I >> O;

		vector<string> ans(n, string(n, 'N'));
		for (int i = 0; i < n; i++) { ans[i][i] = 'Y'; }

		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (ans[i][j - 1] == 'Y' && O[j - 1] == 'Y' && I[j] == 'Y') { ans[i][j] = 'Y'; }
			}
		}
		for (int i = n - 1; i >= 0; i--) {
			for (int j = i - 1; j >= 0; j--) {
				if (ans[i][j + 1] == 'Y' && O[j + 1] == 'Y' && I[j] == 'Y') { ans[i][j] = 'Y'; }
			}
		}

		ofs << "Case #" << qq << ":\n";
		for (auto &s : ans) { ofs << s << '\n'; }
	}
}