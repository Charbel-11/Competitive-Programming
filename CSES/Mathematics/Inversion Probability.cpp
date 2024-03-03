#include <bits/stdc++.h>
using namespace std;
typedef double ld;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n; cin >> n;
    vector<int> r(n); for (auto& x : r) { cin >> x; }

    ld ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ld termI = 0;
        for(int j = i + 1; j < n; j++){
            int cur = 0;
            for(int k = 1; k <= r[i]; k++){
                cur += min(r[j], k - 1);
            }
            termI += (cur + 0.0) / (r[j] + 0.0);
        }
        ans += termI / (r[i] + 0.0);
    }

    if (n >= 10) { ans += 0.0000000000001; }
    cout << setprecision(6) << fixed << ans << '\n';
}