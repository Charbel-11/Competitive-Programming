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

int minSwaps(string &s, int l, int r, char c) {
	if (l == r) { return (s[l] != c); }
	int mid = (l + r) >> 1;

	int c1 = minSwaps(s, l, mid, c + 1);
	for (int k = mid + 1; k <= r; k++) { c1 += s[k] != c; }
	int c2 = minSwaps(s, mid + 1, r, c + 1);
	for (int k = l; k <= mid; k++) { c2 += s[k] != c; }

	return min(c1, c2);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		string s; cin >> s;

		cout << minSwaps(s, 0, n - 1, 'a') << '\n';
	}
}