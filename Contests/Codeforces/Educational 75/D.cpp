#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

vector<pair<ll, ll>> emp;
int n; ll s, minS;

bool bSearch(ll t) {
	int neededBigger = n / 2 + 1;
	ll curS = s-minS;
	for (int i = emp.size() - 1; i >= 0 && neededBigger > 0; i--) {
		if (emp[i].first >= t) {
			neededBigger--;
			continue;
		}
		else if (emp[i].second >= t) {
			ll need = t - emp[i].first;
			if (curS < need) { return false; }
			curS -= need; neededBigger--;
		}
	}
	if (neededBigger > 0) { return false; }
	
	return true;
}

int main() {
	int t; cin >> t;

	while (t--) {
		cin >> n; cin >> s;
		minS = 0;
		emp.clear(); emp.resize(n);
		for (int i = 0; i < n; i++) {
			ll l, r; cin >> l >> r;
			emp[i] = { l,r };
			minS += l;
		}
		sort(emp.begin(), emp.end());

		ll a = 0, b = s;
		while (a < b) {
			ll mid = (a + b + 1) / 2;
			bool curB = bSearch(mid);
			if (curB) {
				a = mid;
			}
			else {
				b = mid - 1;
			}
		}

		cout << a << endl;
	}
}