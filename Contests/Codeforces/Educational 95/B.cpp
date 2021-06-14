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
		vector<int> a(n); for (auto &x : a) { cin >> x; }
		vector<int> l(n); for (auto &x : l) { cin >> x; }

		vector<int> unlocked;
		for (int i = 0; i < n; i++) {
			if (l[i] == 0) { unlocked.push_back(a[i]); }
		}
		sort(unlocked.rbegin(), unlocked.rend());

		int j = 0;
		for (int i = 0; i < n; i++) {
			if (l[i] == 0) { a[i] = unlocked[j++]; }
		}

		for (int i = 0; i < n; i++) { cout << a[i] << ' '; }
		cout << '\n';
	}
}