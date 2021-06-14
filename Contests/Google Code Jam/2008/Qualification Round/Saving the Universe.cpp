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
		string tmp; getline(cin, tmp);
		for (int i = 0; i < n; i++) { 
			getline(cin, tmp); 
		}

		set<string> cur; int ans = 0;
		int q; cin >> q; getline(cin, tmp);
		while (q--) {
			string curS; getline(cin, curS);
			cur.insert(curS);
			if (cur.size() == n) { 
				cur.clear(); cur.insert(curS);
				ans++; 
			}
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}