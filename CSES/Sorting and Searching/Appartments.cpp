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

	int n, m, k; cin >> n >> m >> k;
	vector<int> a(n); for (auto &x : a) { cin >> x; }
	sort(a.begin(), a.end());
	vector<int> b(m); for (auto &x : b) { cin >> x; }
	sort(b.begin(), b.end());

	int i = 0, j = 0, res = 0;
	while (i < n && j < m) {
		if (abs(a[i] - b[j]) <= k) { res++; i++; j++; }
		else if (a[i] < b[j]) { i++; }
		else { j++; }
	}

	cout << res << '\n';
}