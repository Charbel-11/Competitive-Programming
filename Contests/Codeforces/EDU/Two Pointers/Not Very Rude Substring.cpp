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

	int n; ll c; cin >> n >> c;
	string s; cin >> s;

	ll ans = 0, curRude = 0;
	int l = 0, curA = 0, curB = 0;
	for (int r = 0; r < n; r++) {
		if (s[r] == 'a') { curA++; }
		else if (s[r] == 'b') { curB++; curRude += curA; }

		while (curRude > c) {
			if (s[l] == 'a') { curRude -= curB; curA--; }
			else if (s[l] == 'b') { curB--; }
			++l;
		}

		ans = max(ans, (ll)r - l + 1);
	}

	cout << ans << '\n';
}