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
		int n, k; cin >> n >> k;
		string s; cin >> s;

		int cur = 0, ans = 1;
		for(int i = 0; i < n; i++){
			if (s[i] == '*') { cur = i; s[i] = 'x'; break; }
		}

		while (cur < n) {
			int j = min(n - 1, cur + k);
			bool found = false;
			for (; j > cur; j--) {
				if (s[j] == '*') {
					s[j] = 'x'; found = true;
					ans++; cur = j;
					break;
				}
			}
			if (!found) { break; }
		}

		cout << ans << '\n';
	}
}