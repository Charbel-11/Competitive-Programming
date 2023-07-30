#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = (int)2e5 + 2;
bitset<M + 1> dp;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    vector<ll> a(n); for(auto &x : a){ cin >> x; }
    for(int i = 0; i < n; i++){ a.push_back(0); }
    n += n; dp[0] = true;

    bitset<M + 1> mask;
    for(int i = 0; i < M; i++){ mask[i] = true; }
    ll ans = 0, prefSum = 0;
    for(int i = 0; i < n; i++){
        if (prefSum < i){ break; }
        prefSum += a[i];
        if (dp[i]){ ans = max(ans, prefSum - i); }

        dp |= ((dp & mask) << a[i]);
        mask[i] = false;
    }

    cout << ans << '\n';
}