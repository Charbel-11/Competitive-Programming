#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int q; cin >> q;

	while (q--) {
		int n; ll k; cin >> n >> k;
		string s; cin >> s;

		int l = -1;		//last 0
		for (int i = 0; i < n; i++) {
			if (s[i] == '0') {
				int dist = i - (l + 1);
				if (k >= dist) {
					swap(s[i], s[l + 1]);
					l++; k -= dist;
				}
				else {
					swap(s[i], s[i - k]);
					break;
				}
			}
		}
		cout << s << endl;
	}
}