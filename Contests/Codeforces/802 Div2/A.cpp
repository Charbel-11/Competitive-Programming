#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t; cin >> t;
    while(t--){
        ll n, m; cin >> n >> m;
        ll ans = m * (m-1)/2 + m * n * (n+1)/2;
        cout << ans << '\n';
    }
}
