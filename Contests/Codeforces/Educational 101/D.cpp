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

		set<int> special;
		special.insert(n);
		special.insert(max(2, n >> 3));
		if (!special.count(2)) { special.insert(2); }

		vector<pair<int, int>> ans;
		for (int i = 3; i < n; i++) {
			if (!special.count(i)) {
				ans.push_back({ i, i + 1 });
			}
		}

		vector<int> specialA, specialIdx;
		for (auto& it : special) { specialA.push_back(it); specialIdx.push_back(it); }
		int m = specialA.size();

		ans.push_back({ specialIdx[m - 1], specialIdx[m - 2] });
		specialA[m-1] = (specialA[m-1] + specialA[m-2] - 1) / specialA[m-2];
		while (specialA.size() > 2 && specialA[m - 2] != 1) {
			ans.push_back({ specialIdx[m - 2], specialIdx[m - 1] });
			specialA[m - 2] = (specialA[m - 2] + specialA[m - 1] - 1) / specialA[m - 1];
		}
		while (specialA[m - 1] != 1) {
			ans.push_back({ specialIdx[m - 1], specialIdx[0] });
			specialA[m - 1] = (specialA[m - 1] + specialA[0] - 1) / specialA[0];
		}

		cout << ans.size() << '\n';
		//for (auto& p : ans) { cout << p.first << " " << p.second << '\n'; }
	}
}