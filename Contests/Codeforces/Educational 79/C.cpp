#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;
typedef long long ll;

int main() {
	int t; cin >> t;

	while (t--) {
		int n, m; cin >> n >> m;

		map<int, int> ma;
		vector<int> a(n), b(m);
		for (int i = 0; i < n; i++) {
			int te; cin >> te;
			a[i] = te;
			ma.insert({ te, i });
		}
		for (auto &x : b) { cin >> x; }

		long long res = m;
		int changedI = -1;
		for (int i = 0; i < m; i++) {
			int curIdx = ma[b[i]];
			if (curIdx < changedI) { 
				continue;
			}
			res += (curIdx - i) * 2ll;
			changedI = curIdx;
		}

		cout << res << endl;
	}
}