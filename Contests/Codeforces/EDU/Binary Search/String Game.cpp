#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

string p, t;
vector<int> a;

bool check(int mid) {
	int n = p.size(), m = t.size();
	vector<bool> removed(n, 0);
	for (int i = 0; i < mid; i++) { removed[a[i]] = true; }

	int i = 0, j = 0;
	while (i < n && j < m) {
		if (removed[i]) { i++; continue; }
		if (p[i] == t[j]) { i++; j++; continue; }
		i++;
	}

	return j == m;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> p >> t;
	a.resize(p.size()); for (auto& x : a) { cin >> x; x--; }

	int l = 0, r = p.size();
	while (l < r) {
		int mid = (l + r + 1) / 2;
		if (check(mid)) { l = mid; }
		else { r = mid - 1; }
	}

	cout << l << '\n';
}