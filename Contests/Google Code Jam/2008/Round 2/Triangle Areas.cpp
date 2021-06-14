//WA
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
		int n, m, a; cin >> n >> m >> a;

		int x = -1, y = -1;
		/*
		for (int i = 1; i * i <= a; i++) {
			if (a % i) { continue; }
			int d1 = i, d2 = a / i;
			if (d1 <= n && d2 <= m) { x = d1; y = d2; break; }
			if (d1 <= m && d2 <= n) { x = d2; y = d1; break; }
		}
		*/
		for (int i = 0; i <= n && x == -1; i++) {
			for (int j = 0; j <= m; j++) {
				if (i * j == a) { x = i; y = j; break; }
			}
		}

		cout << "Case #" << qq << ": ";
		if (x == -1) { cout << "IMPOSSIBLE\n"; }
		else { cout << "0 0 " << x << " 0 0 " << y << '\n'; }
	}
}