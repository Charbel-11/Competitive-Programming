#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q;
    vector<ll> R(n); for(auto &x : R){ cin >> x; }
    sort(R.begin(), R.end());
    for(int i = 1; i < n; i++){ R[i] += R[i-1]; }

    while(q--){
        ll x; cin >> x;
        int ans = upper_bound(R.begin(), R.end(), x) - R.begin();
        cout << ans << '\n';
    }
}

