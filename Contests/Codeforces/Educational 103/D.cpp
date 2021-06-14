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
		int n; cin >> n;
		string s; cin >> s;
		reverse(s.begin(), s.end()); s.push_back('R');
		reverse(s.begin(), s.end()); s.push_back('L');

		vector<vector<int>> dpL(n + 3, vector<int>(2, 0));
		vector<vector<int>> dpR(n + 3, vector<int>(2, 0));
		for (int i = 1; i <= n + 1; i++) {
			dpL[i][0] = dpL[i][1] = 1;
			if (s[i - 1] == 'L') { dpL[i][0] += dpL[i - 1][1]; }
			else { dpL[i][1] += dpL[i - 1][0]; }
		}

		for (int i = n + 1; i >= 1; i--) {
			dpR[i][0] = dpR[i][1] = 1;
			if (s[i] == 'R') { dpR[i][0] += dpR[i + 1][1]; }
			else { dpR[i][1] += dpR[i + 1][0]; }
		}
		
		for (int i = 1; i <= n + 1; i++) { cout << dpR[i][0] + dpL[i][0] - 1 << ' '; }
		cout << '\n';
	}
}