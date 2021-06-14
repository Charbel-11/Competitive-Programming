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
	int t; cin >> t;

	while (t--) {
		ll n, x; cin >> n >> x;
		vector<ll> wealth(n);
		for (auto &y : wealth) { cin >> y; }
		sort(wealth.begin(), wealth.end());

		ll ans = 0;
		ll curSum = 0;
		for (int i = n - 1; i >= 0; i--) {
			curSum += wealth[i];
			if (wealth[i] >= x) { ans++; }
			else {
				ll newDist = curSum / (ans + 1);
				if (newDist >= x) { ans++; }
				else { break; }
			}
		}
		cout << ans << endl;
	}
}