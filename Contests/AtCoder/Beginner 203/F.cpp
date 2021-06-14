#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int dp[200005][35];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, k; cin >> n >> k;
    vector<int> A(n); for (auto& x : A) { cin >> x; }
    sort(A.begin(), A.end());

    for (int i = 0; i < n; i++) {
        dp[i][0] = i + 1;
        for (int j = 1; j < 35; j++) {
            dp[i][j] = (i ? dp[i - 1][j] : 0) + 1;
            int idx = upper_bound(A.begin(), A.end(), A[i] / 2) - A.begin() - 1;
            if (idx >= 0) { dp[i][j] = min(dp[i][j], dp[idx][j - 1]); }
            else { dp[i][j] = 0; }
        }
    }

    int ans1 = 35, ans2 = k;
    for (int j = 0; j < 35; j++) {
        if (dp[n - 1][j] <= k) {
            ans1 = j; ans2 = dp[n - 1][j];
            break;
        }
    }

    cout << ans1 << " " << ans2 << '\n';
}