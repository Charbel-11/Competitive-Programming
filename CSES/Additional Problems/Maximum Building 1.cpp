#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <stack>
#include <algorithm>
using namespace std;
typedef long long ll;

int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    if (n == 0) { return 0; }
    stack<int> S; S.push(-1);
    int ans = 0;

    for (int i = 0; i < n; i++) {
        while (S.size() > 1 && heights[i] < heights[S.top()]) {
            int curHeight = heights[S.top()];
            S.pop();
            int range = i - (S.top() + 1);
            ans = max(ans, range * curHeight);
        }
        S.push(i);
    }

    while (S.size() > 1) {
        int curHeight = heights[S.top()];
        S.pop();
        ans = max(ans, (n - (S.top() + 1)) * curHeight);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m; cin >> n >> m; int ans = 0;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == '.') { grid[i][j] = 1 + (i ? grid[i - 1][j] : 0); }
        }
        ans = max(ans, largestRectangleArea(grid[i]));
    }

    cout << ans << '\n';
}