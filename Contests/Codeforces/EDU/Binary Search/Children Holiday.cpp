#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int m, n;
vector<int> work, z, rest;
bool check(int t, vector<int>& res) {
	res.clear(); res.resize(n, 0);
	int total = 0;
	for (int i = 0; i < n; i++) {
		int curT = t, cnt = t/(z[i] * work[i] + rest[i]);
		res[i] = cnt * z[i];
		curT -= cnt * (z[i] * work[i] + rest[i]);
		res[i] += min(z[i], curT / work[i]);
		total += res[i];
		if (total >= m) { res[i] -= (total - m); return true; }
	}
	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> m >> n;
	work.resize(n); z.resize(n); rest.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> work[i] >> z[i] >> rest[i];
	}

	vector<int> res;
	int l = 0, r = m * 200;
	while (l < r) {
		int mid = (l + r) / 2;
		if (check(mid, res)) { r = mid; }
		else { l = mid + 1; }
	}

	check(l, res);
	cout << l << '\n';
	for (auto& x : res) { cout << x << ' '; }
}