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

	int n, m; cin >> n >> m;
	vector<int> x(n); for (auto& xx : x) { cin >> xx; }
	vector<int> idx(n + 2), diff(n + 2, 0); idx[0] = n + 2; idx[n + 1] = n + 3;
	for (int i = 1; i <= n; i++) { idx[x[i - 1]] = i; }

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (idx[i] < idx[i - 1]) { diff[i] = 1; ans++; }
	}

	while (m--) {
		int a, b; cin >> a >> b;
		swap(x[a - 1], x[b - 1]);
		swap(idx[x[a - 1]], idx[x[b - 1]]);
		a = x[a - 1]; b = x[b - 1];

		ans -= (diff[a] + diff[a + 1]);
		diff[a] = diff[a + 1] = 0;
		ans -= (diff[b] + diff[b + 1]);
		diff[b] = diff[b + 1] = 0;
		if (idx[a] < idx[a - 1]) { diff[a] = 1; ans++; }
		if (idx[a + 1] < idx[a]) { diff[a + 1] = 1; ans++; }
		if (diff[b] == 0 && idx[b] < idx[b - 1]) { diff[b] = 1; ans++; }
		if (diff[b+1] == 0 && idx[b + 1] < idx[b]) { diff[b + 1] = 1; ans++; }

		cout << ans << '\n';
	}
}