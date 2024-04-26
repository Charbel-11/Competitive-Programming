#include <iostream>
using namespace std;
typedef long long ll;

ll DP[1000001]; ll r, p;
ll getDP(int n){
    if (DP[n] != (1ll<<60)){ return DP[n]; }
    for (int i = n - 1; i > 0; --i) {
        int cuts = i + 1, target = (n + cuts - 1) / cuts;
        DP[n] = min(DP[n], i * p + getDP(target));
    }
    DP[n] += r;
    return DP[n];
}

int main() {
    int N; cin >> N >> r >> p;
    fill(DP, DP + N + 1, 1ll << 60);
    DP[1] = 0; getDP(N);
    cout << DP[N] << '\n';
}