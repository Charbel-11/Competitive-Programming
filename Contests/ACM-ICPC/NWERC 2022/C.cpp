#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll Sqrt(ll x){
    ll L = max(0, (int)(sqrt(x) - 10));
    ll R = sqrt(x) + 10;
    while(L != R){
        ll mid = (L + R + 1) >> 1;
        mid * mid > x ? R = mid - 1 : L = mid;
    }
    return L;
}

ll FindSquareRadius(ll x){
    ll L = 0;
    ll R = x;
    while(L != R){
        ll mid = (L + R + 1) >> 1;
        2ll * mid * mid > x ? R = mid - 1 : L = mid;
    }
    return L;
}

ll CountLatticePoints(ll R2){
    ll square_radius = FindSquareRadius(R2);
    ll res = (square_radius * square_radius) << 2;
    for(ll x = square_radius + 1; x * x <= R2; ++x){
        ll y2_bound = R2 - x * x;
        res += (Sqrt(y2_bound) << 1) << 2;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll s; cin >> s;
    ll l = 0, r = 1 << 30;
    while(l != r){
        ll mid = (l + r) >> 1;
        CountLatticePoints(mid) <= s ? l = mid + 1 : r = mid;
    }
    cout << fixed << setprecision(10) << sqrt(l) << '\n';
}