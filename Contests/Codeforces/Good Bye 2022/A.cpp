#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n, m; cin >> n >> m;

        multiset<ll> nums;
        for(int i = 0; i < n; i++){
            ll x; cin >> x;
            nums.insert(x);
        }
        for(int j = 0; j < m; j++){
            ll y; cin >> y;
            nums.erase(nums.begin());
            nums.insert(y);
        }

        ll ans = 0;
        for(auto &x : nums){ ans += x; }
        cout << ans << '\n';
	}
}