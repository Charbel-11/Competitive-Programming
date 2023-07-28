#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n; cin >> n;
    string s; cin >> s;
    vector<ll> cnt(n, 0);

    for(int i = 0; i < n; i++){
        if (s[i] == '0'){ cnt[i] = i; }
        else{
            cnt[i] = 1;
            if (i > 0){
                if (s[i-1] == '0'){ cnt[i]++; continue; }
                cnt[i] += (i-cnt[i-1]);
            }
        }
    }

    ll ans = 0;
    for(auto &x : cnt){ ans += x; }
    cout << ans << '\n';
}