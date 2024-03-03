#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// assumes L = 0
ll getCount(ll R, ll M){
    return 1 + R / M;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll A, M, L, R; cin >> A >> M >> L >> R;
    L -= A; R -= A;
    if (R < 0){ swap(L, R); L = -L; R = -R; }
    ll ans = getCount(R, M);
    if (L > 0){
        ans -= getCount(L - 1, M);
    }
    else if (L < 0){
        ans += getCount(-L,M) - 1;
    }
    cout << ans << '\n';
}

