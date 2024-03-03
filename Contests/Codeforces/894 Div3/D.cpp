#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		ll n; cin >> n;

        ll l = 1, r = 3e9;
        while (l < r){
            ll mid = l + (r-l)/2;
            ll cur = mid * (mid-1) / 2;
            if (cur >= n) { r = mid; }
            else { l = mid + 1; }
        }

        ll ans = l;
        if (l * (l - 1) / 2 > n){
            ans = l-1 + n - ((l-1) * (l-2) / 2);
        }
        cout << ans << '\n';
	}
}