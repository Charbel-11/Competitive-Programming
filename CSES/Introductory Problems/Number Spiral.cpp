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
		int i, j; cin >> i >> j; i--; j--;
		int diag = max(i, j);
		ll num = (ll)diag * (diag + 1) + 1;
		if (diag == i) {
			if (diag % 2) { num += (i - j); }
			else { num -= (i - j); }
		}
		else {
			if (diag % 2) { num -= (j - i); }
			else { num += (j - i); }
		}
		cout << num << '\n';
	}
}