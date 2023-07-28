#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		ll n, k; cin >> n >> k;
        vector<ll> a(n); for(auto &x : a){ cin >> x; }

        if (a[0] != 1){ cout << 1 << '\n'; continue; }

        ll ans = 1, curCovered = 0;
        for(int i = 1; i < n; i++){
            curCovered += a[i] - a[i-1] - 1;
            if (curCovered >= ans){
                ll iterationsThere = (curCovered - ans + 1 + i - 1) / i;
                iterationsThere = min(iterationsThere, k);
                k -= iterationsThere;
                ans += i * iterationsThere;
            }
        }
        ans += n * k;

        cout << ans << '\n';
	}
}