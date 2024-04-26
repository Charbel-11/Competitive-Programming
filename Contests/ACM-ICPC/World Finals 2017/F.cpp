#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr ll INF = 1ll << 60;

ll DP[256][256][256];
ll cost[256][256];

vector<ll> freq;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int d, K; cin >> d >> K; freq.resize(256, 0);
    fill(DP[0][0], DP[0][0] + 256 * 256 * 256, INF);
    fill(cost[0], cost[0] + 256 * 256, 0);
    for(int i = 0; i < d; ++i) {
        ll r, p; cin >> r >> p; freq[r] = p;
    }

    if(K == d) { cout << "0\n"; return 0; }

    for(int L = 0; L < 256; ++L)
        for(int R = L + 2; R < 256; ++R)
            for(int i = L + 1; i < R; ++i)
                cost[L][R] += min(i - L, R - i) * min(i - L, R - i) * freq[i];

    for(int i = 0; i < 256; ++i)
        for(int L = 0; L <= i; ++L) {
            DP[i][L][1] = 0;
            for(int j = 0; j <= i; ++j)
                DP[i][L][1] += (j - L) * (j - L) * freq[j];
        }

    for(int i = 0; i < 256; ++i) {
        for(int L = 0; L <= i; ++L) {
            for(int k = 2; k <= min(K, i + 1); ++k) {
                if (L == i) {
                    for(int j = 0; j < i; ++j)
                        DP[i][L][k] = min(DP[i][L][k], DP[j][j][k - 1] + cost[j][i]);
                }
                else {
                    DP[i][L][k] = DP[i - 1][L][k] + (i - L) * (i - L) * freq[i];
                }
            }
        }
    }
    ll res = INF;
    for(int i = 0; i < 256; i++)
        res = min(res, DP[255][i][K]);
    cout << res << '\n';
}