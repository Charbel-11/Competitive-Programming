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
		int n, l, r; cin >> n >> l >> r;
		vector<int> socksL(n, 0), socksR(n, 0);

		for (int i = 0; i < l; i++) {
			int cur; cin >> cur; cur--;
			socksL[cur]++;
		}
		for (int i = 0; i < r; i++) {
			int cur; cin >> cur; cur--;
			socksR[cur]++;
		}

		int sL = 0, sR = 0;
		for (int i = 0; i < n; i++) {
			int common = min(socksL[i], socksR[i]);
			socksL[i] -= common; socksR[i] -= common;
			sL += socksL[i]; sR += socksR[i];
		}

		if (sL < sR) { swap(socksL, socksR); swap(sL, sR); }
		int ans = 0, dif = sL - sR;

		for (int i = 0; i < n && dif; i++) {
			while (socksL[i] >= 2 && dif) { dif -= 2; socksL[i] -= 2; sL -= 2; ans++; }
		}

		ans += sL;
		cout << ans << '\n';
	}
}
