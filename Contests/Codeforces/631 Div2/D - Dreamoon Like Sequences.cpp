#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
ll mod;

int main() {
	int t; cin >> t;
	while (t--) {
		ll d; cin >> d >> mod;
		
		ll ans = 1, cur = 1;
		while (true) {
			if (cur * 2 > d) {
				cur = d - cur + 1;
				ans *= (cur + 1); ans %= mod;
				break;
			}

			ans *= (cur + 1); ans %= mod;
			cur *= 2;
		}

		ans--; while (ans < 0) { ans += mod; }
		cout << ans << endl;
	}
}