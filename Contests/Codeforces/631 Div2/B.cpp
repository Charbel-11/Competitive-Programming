#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		vector<int> a(n);
		for (auto &x : a) { cin >> x; }
		
		vector<int> l1(n + 2, 0), l2(n + 2, 0);
		int f1, f2, prefix1, prefix2;
		f1 = f2 = 0; prefix1 = prefix2 = 0;

		for (int i = 0; i < n; i++) {
			l2[a[i]]++;
			if (l2[a[i]] == 2) { f2++; }
			if (prefix2 == a[i] - 1) {
				int temp = a[i];
				while (l2[temp] != 0) { prefix2 = temp++; }
			}
		}

		vector<pair<int, int>> ans;
		for (int i = 0; i < n; i++) {
			l2[a[i]]--; l1[a[i]]++;
			if (l2[a[i]] == 1) { f2--; }
			if (l2[a[i]] == 0) { prefix2 = min(prefix2, a[i] - 1); }

			if (l1[a[i]] == 2) { break; }
			if (l1[a[i]] == 1 && prefix1 == a[i] - 1) {
				int temp = a[i];
				while (l1[temp] != 0) { prefix1 = temp++; }
			}

			if (f1 == 0 && f2 == 0 && prefix1 + prefix2 == n) {
				ans.push_back({ prefix1, prefix2 });
			}
		}

		cout << ans.size() << endl;
		for (auto& p : ans) { cout << p.first << " " << p.second << endl; }
	}
}