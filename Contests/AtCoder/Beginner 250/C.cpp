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

	int n, q; cin >> n >> q;
	vector<int> pos(n + 1), ans(n);
	for (int i = 1; i <= n; i++) { pos[i] = i - 1; ans[i - 1] = i; }

	while (q--) {
		int x; cin >> x;
		int curPos = pos[x];
		if (curPos == n - 1) { curPos--; }

		swap(ans[curPos], ans[curPos + 1]);
		pos[ans[curPos]] = curPos;
		pos[ans[curPos + 1]] = curPos + 1;
	}

	for (auto& x : ans) { cout << x << ' '; }
	cout << '\n';
}
