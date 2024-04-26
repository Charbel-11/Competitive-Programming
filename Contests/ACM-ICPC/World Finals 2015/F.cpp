#include <bits/stdc++.h>
using namespace std;

const int INF = 52*52*10000+10;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int r, c; cin >> r >> c;
    vector<string> grid(r); for(auto &s : grid){ cin >> s; }

    string target; cin >> target;
    target.push_back('*');
    int m = target.size();

    vector<vector<pair<int, int>>> edges(r*c);
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            char curC = grid[i][j];
            for(int k = 0; k < 4; k++){
                int ni = i + dx[k], nj = j + dy[k];
                while(ni < r && ni >= 0 && nj < c && nj >= 0 && grid[ni][nj] == curC){
                    ni += dx[k]; nj += dy[k];
                }
                if (ni < r && ni >= 0 && nj < c && nj >= 0)
                    edges[i*c+j].emplace_back(ni, nj);
            }
        }
    }

    vector<vector<int>> oldDP(52, vector<int>(52, INF));
    for(int k = 0; k <= m; k++){
        vector<vector<int>> dp(52, vector<int>(52, INF));
        vector<vector<bool>> vis(52, vector<bool>(52, false));
        queue<pair<int, int>> Q;

        vector<pair<int, pair<int, int>>> starts; int startIdx = 0;
        if (k == 0) {
            dp[0][0] = 0; Q.emplace(0, 0); vis[0][0] = true;
            starts.push_back({0, {0, 0}}); startIdx++;
        }
        else {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if (grid[i][j] == target[k-1] && oldDP[i][j] < INF) {
                        dp[i][j] = 1 + oldDP[i][j];
                        starts.push_back({dp[i][j], {i, j}});
                    }
                }
            }

            sort(starts.begin(), starts.end());
            while(startIdx < starts.size() && starts[startIdx].first == starts[0].first){
                auto p = starts[startIdx].second;
                vis[p.first][p.second] = true;
                Q.emplace(starts[startIdx++].second);
            }
        }

        while(!Q.empty()){
            auto [i, j] = Q.front(); Q.pop();
            while(startIdx < starts.size() && starts[startIdx].first == dp[i][j] + 1){
                auto p = starts[startIdx++].second;
                if (vis[p.first][p.second]){ continue; }
                vis[p.first][p.second] = true; Q.emplace(p);
            }
            for(auto [ni, nj] : edges[i*c+j]){
                if (vis[ni][nj]){ continue; }
                dp[ni][nj] = dp[i][j] + 1;
                vis[ni][nj] = true; Q.emplace(ni, nj);
            }
        }

        swap(dp, oldDP);
    }

    int ans = INF;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if (grid[i][j] == '*') {
                ans = min(ans, oldDP[i][j]);
            }
        }
    }
    cout << ans << '\n';
}