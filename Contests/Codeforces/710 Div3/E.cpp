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

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<int> q(n); for (auto& x : q) { cin >> x; }

		set<int> avMin, avMax;
		for (int i = 1; i <= n; i++) { avMin.insert(i); avMax.insert(i); }
		for(auto &x : q){
			if (avMin.count(x)) { avMin.erase(x); avMax.erase(x); }
		}

		vector<int> minP(n), maxP(n);
		minP[0] = maxP[0] = q[0];
		for (int i = 1; i < n; i++) {
			if (q[i] != q[i - 1]) { minP[i] = maxP[i] = q[i]; }
			else {
				minP[i] = *avMin.begin(); avMin.erase(avMin.begin());

				auto it = prev(avMax.upper_bound(q[i]));
				maxP[i] = *(it); avMax.erase(it);
			}
		}

		for (auto& x : minP) { cout << x << ' '; } cout << '\n';
		for (auto& x : maxP) { cout << x << ' '; } cout << '\n';
	}
}