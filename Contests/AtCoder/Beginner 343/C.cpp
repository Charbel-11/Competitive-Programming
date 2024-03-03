#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll n; cin >> n;
    ll cur = 1, ans = 1;
    while(cur * cur * cur <= n){
        ll k = cur * cur * cur;
        string s = to_string(k);
        string sRev = s; reverse(sRev.begin(), sRev.end());
        if (s == sRev){ ans = k; }
        cur++;
    }

    cout << ans << '\n';
}

