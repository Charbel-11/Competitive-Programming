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
		int n, k; cin >> n >> k;
		if (k >= n) { cout << 1 << endl; continue; }

		int d = 2;
		int ans = n;
		while (d*d <= n) {
			if (n%d == 0){
				if (n / d <= k) { ans = min(ans, d); }
				if (d <= k) { ans = min(ans, n / d); }
			}
			d++; 
		}
		
		cout << ans << endl;
	}
}