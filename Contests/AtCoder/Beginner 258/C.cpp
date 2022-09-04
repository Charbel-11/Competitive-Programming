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

	int n, q; cin >> n >> q;
	string s; cin >> s;

	int rot = 0;
	while (q--) {
		int t, x; cin >> t >> x;
		if (t == 1) {
			rot += x; rot %= n;
		}
		else {
			if (x > rot) { cout << s[x - rot - 1] << '\n'; }
			else { cout << s[n - rot + x - 1] << '\n'; }
		}
	}
}
