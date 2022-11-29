#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll x; cin >> x;
    ll lim = 1;
    while(lim <= x){ lim *= 2; }

    vector<ll> cnt(lim, 0);
    for(int k = 0; k < lim; k++){
        ll num = (k * x) ^ x;
        if (gcd(num, x) == 1){
            cnt[k] = 1;
        }
    }

    partial_sum(cnt.begin(), cnt.end(), cnt.begin());

    int n; cin >> n;
    for(int i = 0; i < n; i++){
        ll l, r; cin >> l >> r;

        if(x == 1){
            cout << r-l+1 << '\n';
            continue;
        }

        int curL = l%lim, curR = r%lim;
        ll full = ((r - curR) - (l + lim - curL)) / lim;
        ll res = full * cnt.back();
        res += cnt.back() - (curL ? cnt[curL - 1] : 0);
        res += cnt[curR];

        cout << res << '\n';
    }
}