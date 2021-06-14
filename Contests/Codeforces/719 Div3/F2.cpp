#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int query(int l, int r) {
	cout << "? " << l << " " << r << endl;
	int ans; cin >> ans;
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, t; cin >> n >> t;
	int k; cin >> k;

	int m = (n + 9) / 10;
	vector<int> segments(m, 0);
	for(int i = 0; i < m; i++){
		int curL = i * 10 + 1, curR = (i + 1) * 10;
		curR = min(curR, n);
		segments[i] = curR - curL + 1 - query(curL, curR);
	}

	while (t--) {
		int l = 1, r = 10;

		for (int i = 0; i < m; i++) {
			if (k <= segments[i]) { break; }
			k -= segments[i];
			l += 10; r += 10; 
		}
		r = min(r, n);

		while (l < r) {
			int mid = (l + r) >> 1;
			int s = query(l, mid);
			int zeros = mid - l + 1 - s;
			if (k > zeros) {
				k -= zeros;
				l = mid + 1;
			}
			else {
				r = mid;
			}
		}

		segments[(l - 1) / 10]--;

		cout << "! " << l << endl;
		if (t) { cin >> k; }
	}
}
