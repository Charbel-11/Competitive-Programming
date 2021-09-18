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
	for (int qq = 1; qq <= t; qq++) {
		int n; cin >> n;
		string s; cin >> s;
		vector<int> dist(n, n);
		
		int last = -n;
		for (int i = 0; i < n; i++) {
			if (s[i] == '1') { last = i; }
			dist[i] = i - last;
		}
		last = 2 * n;
		for (int i = n - 1; i >= 0; i--) {
			if (s[i] == '1') { last = i; }
			dist[i] = min(dist[i], last - i);
		}

		ll ans = 0;
		for (auto& x : dist) { ans += x; }
		cout << "Case #" << qq << ": " << ans << '\n';
	}
}
