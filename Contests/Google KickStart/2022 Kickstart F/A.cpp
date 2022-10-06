#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        int n; cin >> n;
        vector<pair<string, int>> A(n);
        vector<pair<int, int>> C(n);

        for(int i = 0; i < n; i++){
            string c; int d, u; cin >> c >> d >> u;
            A[i] = {c, u}; C[i] = {d, u};
        }

        sort(A.begin(), A.end());
        sort(C.begin(), C.end());

        int ans = 0;
        for(int i = 0; i < n; i++){
            ans += A[i].second == C[i].second;
        }

        cout << "Case #" << qq << ": " << ans << '\n';
    }
}
