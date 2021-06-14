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

	int n, p; cin >> n >> p;
	vector<int> a(n);
	for (auto &x : a) { cin >> x; }
	sort(a.begin(), a.end());

	vector<int> ans;
	for (int x = 1; x <= 2000; x++) {
		int streak = 0, candies = x;
		bool OK = true;
		for (int i = 0; i < n; i++) {
			if (candies + streak < a[i]) { OK = false; break; }
			if (candies >= a[i]) { streak++; continue; }
			if (streak >= p) { OK = false; break; }
			int dif = a[i] - candies;
			candies += dif; streak -= dif; streak++;
		}
		if (streak >= p) { OK = false; }
		if (OK) { ans.push_back(x); }
	}

	cout << ans.size() << '\n';
	for (auto &x : ans) { cout << x << ' '; }
	cout << '\n';
}