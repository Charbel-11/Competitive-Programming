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
vector<ll> a;

bool check(int T) {
	ll maxAdd = (1ll << T) - 1;
	vector<ll> curA = a;
	curA[a.size() - 1] += maxAdd;
	for (int i = a.size() - 2; i >= 0; i--) {
		if (curA[i] > curA[i + 1]) { return false; }
		curA[i] = min(curA[i] + maxAdd, curA[i + 1]);
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		a.clear(); a.resize(n);
		for (auto &x : a) { cin >> x; }

		int l = 0, r = 55;
		while (l < r) {
			int mid = (l + r) / 2;
			bool b = check(mid);
			if (b) { r = mid; }
			else { l = mid + 1; }
		}
		cout << l << endl;
	}
}