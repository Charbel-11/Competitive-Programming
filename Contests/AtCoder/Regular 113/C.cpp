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

	string s; cin >> s;
	int n = s.size();

	ll ans = 0; int lastEq = n;
	for (int i = n - 3; i >= 0; i--) {
		if (s[i] == s[i+1]){
			int j = i + 2;
			while (j < lastEq) {
				if (s[j] != s[i]) ans++;
				j++;
			}
			if (j == lastEq && j < n && s[j] != s[i]) { ans += (n - lastEq); }

			lastEq = i;
		}
	}

	cout << ans << '\n';
}