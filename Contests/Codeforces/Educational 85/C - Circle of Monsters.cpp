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

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<ll> a(n), b(n);
		for (int i = 0; i < n; i++) { cin >> a[i] >> b[i]; }
		for (int i = 0; i < n; i++) { b[i] = min(b[i], a[(i + 1) % n]); }
		
		ll curCost = a[0];
		for (int i = 1; i < n; i++) { curCost += (a[i] - b[i - 1]); }
		ll finalCost = curCost;
		for (int i = 1; i < n; i++) {
			curCost += (b[i - 1] - b[(i + n - 2)%n]);
			finalCost = min(curCost, finalCost);
		}
		cout << finalCost << '\n';
	}
}