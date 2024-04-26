#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; ll m; cin >> n >> m;

    ll ans = n;
    multiset<ll> a;
    for(int i = 0; i < n; i++){
        ll cur; cin >> cur;
        a.insert(cur);
        ans += cur;
    }

    ll cur = -1;
    while(true){
        if (cur == -1) { cur = *a.rbegin(); }

        a.erase(a.find(cur));
        if (a.empty()){ break; }

        ll maxFit = m - cur;
        auto it = a.upper_bound(maxFit);
        if (it != a.begin()) {
            it = prev(it);
            ans--;
            cur = *it;
        }
        else{
            cur = -1;
        }
    }

    cout << ans << '\n';
}