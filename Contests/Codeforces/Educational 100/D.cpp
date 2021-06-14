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

int n;
vector<int> a, b;

int x1Works(int mid) {
	mid--;
	for (int i = mid, j = n-1; i >= 0; i--, j--) {
		if (a[i] > b[j]) { return false; }
	}
	return true;
}
int x2Works(int mid) {
	mid--;
	for (int i = mid, j = n - 1; i >= 0; i--, j--) {
		if (b[i] > a[j]) { return false; }
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		cin >> n;
		set<int> used;
		a.clear(); b.clear();
		b.resize(n);
		for (auto& x : b) { cin >> x; used.insert(x); }
		for (int i = 1; i <= 2 * n; i++) {
			if (used.count(i)) { continue; }
			a.push_back(i);
		}

		if (a[0] > b[n - 1] || a[n - 1] < b[0]) { cout << 1 << '\n'; continue; }

		int l = 1, r = n;
		while (l < r) {
			int mid = (l + r + 1) / 2;
			if (x2Works(mid)) { l = mid; }
			else { r = mid - 1; }
		}
		int x1 = l;

		l = 1; r = n;
		while (l < r) {
			int mid = (l + r + 1) / 2;
			if (x1Works(mid)) { l = mid; }
			else { r = mid - 1; }
		}
		int x2 = l;

		int ans = 0;
		for (int x = 0; x <= x1; x++) {
			if (x2 >= n - x) { ans++; }
		}
		cout << ans << '\n';
	}
}