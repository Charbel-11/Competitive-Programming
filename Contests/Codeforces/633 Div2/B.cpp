#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
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
		vector<int> a(n);
		for (auto &x : a) { cin >> x; }

		sort(a.begin(), a.end());
		vector<int> ans;
		int i = 0, j = n - 1;
		while (i <= j) {
			if (i == j) { ans.push_back(a[i]); break; }
			ans.push_back(a[i]); ans.push_back(a[j]);
			i++; j--;
		}
		for (int i = n - 1; i >= 0; i--) {
			cout << ans[i] << " ";
		}
		cout << endl;
	}
}