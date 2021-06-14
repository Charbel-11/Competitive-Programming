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
		int n, m; cin >> n >> m;

		int c1 = n / 2; c1 *= m;
		if (n % 2) { c1 += (m + 1) / 2; }

		int c2 = m / 2; c2 *= n;
		if (m % 2) { c2 += (n + 1) / 2; }

		cout << min(c1,c2) << endl;
	}
}