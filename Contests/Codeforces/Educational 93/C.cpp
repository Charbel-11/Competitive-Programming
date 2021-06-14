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
		int n; cin >> n;
		vector<int> a(n);
		string s; cin >> s;
		for (int i = 0; i < n; i++) { a[i] = s[i] - '0' - 1; }
		
		ll ans = 0;
		map<int, int> occ; occ[0] = 1;
		int pref = 0;
		for (int i = 0; i < n; i++) {
			pref += a[i]; 
			ans += occ[pref];
			occ[pref]++;
		}

		cout << ans << '\n';
	}
}