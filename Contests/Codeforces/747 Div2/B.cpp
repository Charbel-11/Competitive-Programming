#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n, k; cin >> n >> k;
		
		ll curN = 1, ans = 0;
		while (k) {
			if (k & 1) { ans += curN; ans %= mod; }
			curN *= n; curN %= mod; 
			k /= 2;
		}

		cout << ans << '\n';
	}
}