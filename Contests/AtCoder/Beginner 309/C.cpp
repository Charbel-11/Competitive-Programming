#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; ll k; cin >> n >> k;

    ll total = 0;
    vector<pair<ll, ll>> v(n);
    for(int i = 0; i < n; i++){
        ll a, b; cin >> a >> b;
        v[i] = {a, b};
        total += b;
    }
    sort(v.begin(), v.end());

    ll ans = 1;
    for(int i = 0; i < n && total > k; i++){
        total -= v[i].second;
        ans = v[i].first + 1;
    }

    cout << ans << '\n';
}