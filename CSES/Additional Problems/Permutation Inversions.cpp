#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9+7;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, k; cin >> n >> k;
    vector<ll> prevDP(k+1, 1), curDP(k+1, 0);

    for(int i = 2; i <= n; i++){
        for(int j = 0; j <= k; j++){
            int maxCurCont = min(j, i - 1);
            int start = j - maxCurCont;

            curDP[j] = prevDP[j] - (start ? prevDP[start-1] : 0);
            curDP[j] %= mod;

            if (j){
                curDP[j] += curDP[j-1];
                curDP[j] %= mod;
            }
        }

        swap(prevDP, curDP);
    }

    ll ans = prevDP[k] - (k ? prevDP[k-1] : 0);
    ans %= mod;
    if (ans < 0){ ans += mod; }
    cout << ans << '\n';
}