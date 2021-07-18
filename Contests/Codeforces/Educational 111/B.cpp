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
		int n, a, b; cin >> n >> a >> b;
		string s; cin >> s;
		int ans = n * a;

		if (b >= 0) { ans += n * b; }
		else {
			int alt = 1;
			for (int i = 1; i < n; i++) {
				if (s[i] != s[i - 1]) { alt++; }
			}
			ans += (1 + (alt / 2)) * b;
		}

		cout << ans << '\n';
	}
}