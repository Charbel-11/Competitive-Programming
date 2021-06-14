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

	int l = 1, r = n;
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

	cout << "! " << l << endl;
}
