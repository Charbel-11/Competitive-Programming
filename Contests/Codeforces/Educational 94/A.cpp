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
		string s; cin >> s;
		string ans(n, '0');
		for (int i = 0; i < n; i++) { ans[i] = s[i*2]; }
		cout << ans << '\n';
	}
}