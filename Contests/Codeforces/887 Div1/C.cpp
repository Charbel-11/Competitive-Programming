#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; ll k; cin >> n >> k;
        vector<ll> v(n); for(auto &x : v){ cin >> x; x %= k; }

        ll ans = v[0]; multiset<ll> incCost;
        for(int i = 1; i < n; i++){
            if (v[i] == v[i-1]){ continue; }
            if (v[i] < v[i-1]){ incCost.insert(k + v[i] - v[i-1]); continue; }
            incCost.insert(v[i] - v[i-1]);
            auto it = incCost.begin();
            ans += *it;
            incCost.erase(it);
        }

        cout << ans << '\n';
    }
}