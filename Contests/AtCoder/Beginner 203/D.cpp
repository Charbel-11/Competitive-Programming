#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, k;
bool check(vector<vector<int>> grid, int med) {
    int neededOnes = k * k - k * k / 2;

    for (auto& v : grid) {
        for (auto& x : v) {
            if (x <= med) { x = 1; }
            else { x = 0; }
        }
    }

    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = grid[i][j];
            if (i) { dp[i][j] += dp[i - 1][j]; }
            if (j) { dp[i][j] += dp[i][j - 1]; }
            if (i && j) { dp[i][j] -= dp[i - 1][j - 1]; }
        }
    }

    for (int i = k - 1; i < n; i++) {
        for (int j = k - 1; j < n; j++) {
            int curSquare = dp[i][j];
            if (i >= k) { curSquare -= dp[i - k][j]; }
            if (j >= k) { curSquare -= dp[i][j - k]; }
            if (i >= k && j >= k) { curSquare += dp[i - k][j - k]; }
            if (curSquare >= neededOnes) { return true; }
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> k;
    vector<vector<int>> grid(n, vector<int>(n));
    for (auto& v : grid)
        for (auto& x : v)
            cin >> x;

    int l = 0, r = 1e9 + 2;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(grid, mid)) { r = mid; }
        else { l = mid + 1; }
    }

    cout << l << '\n';
}
