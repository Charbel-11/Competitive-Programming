#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		ll n, c; cin >> n >> c;
        vector<ll> s(n); for(auto &x : s){ cin >> x; }

        ll si2 = 0, si = 0;
        for(auto &x : s){ si2 += x*x; si += x; }

        ll l = 1, r = sqrt((c+n-1)/n) + 1;
        while (l < r){
            ll mid = (l + r + 1) / 2ll;
            ll rhs = 4ll * n * mid * mid + 4ll * mid * si + si2;
            assert(rhs > 0);
            if (rhs > c){ r = mid - 1; }
            else{ l = mid; }
        }

        cout << l << '\n';
	}
}