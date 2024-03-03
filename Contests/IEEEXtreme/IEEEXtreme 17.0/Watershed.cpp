#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for(auto &v : grid){
        for(auto &x : v){ cin >> x; }
    }

    vector<pair<int, pair<int, int>>> nums;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            nums.push_back({grid[i][j], {i, j}});
        }
    }
    sort(nums.rbegin(), nums.rend());

    vector<vector<double>> drainage(n, vector<double>(m, 1));
    for(int o = 0; o < m * n; o++) {
        int curVal = nums[o].first;
        auto [i, j] = nums[o].second;
        int cnt = 0;
        for (int k = 0; k < 4; k++) {
            int ni = i + dx[k], nj = j + dy[k];
            if (ni >= 0 && nj >= 0 && ni < n && nj < m && grid[ni][nj] < curVal){
                cnt++;
            }
        }
        if (cnt > 0) {
            double division = drainage[i][j] / cnt;
            drainage[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k], nj = j + dy[k];
                if (ni >= 0 && nj >= 0 && ni < n && nj < m && grid[ni][nj] < curVal) {
                    drainage[ni][nj] += division;
                }
            }
        }
    }

    double ans = drainage[0][0];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ans = max(ans, drainage[i][j]);
        }
    }

    cout << setprecision(6) << fixed << ans << '\n';
}

