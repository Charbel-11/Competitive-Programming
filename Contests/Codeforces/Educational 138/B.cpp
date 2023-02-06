#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        ll ans = 0;
        vector<ll> a(n); for(auto &x : a) { cin >> x; ans += x; }
        vector<ll> b(n); for(auto &x : b) { cin >> x; ans += x; }

        ans -= *max_element(b.begin(), b.end());
        cout << ans << '\n';
	}
}