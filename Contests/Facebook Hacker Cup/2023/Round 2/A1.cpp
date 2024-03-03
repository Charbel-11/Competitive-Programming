#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int r, c;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void dfs(int i, int j, int idx, int& freq,
         const vector<vector<int>>& grid, vector<vector<bool>>& vis, set<pair<int, int>>& visEmpty){
    vis[i][j] = true;
    for(int k = 0; k < 4; k++){
        int ni = i + dx[k], nj = j + dy[k];
        if (ni < r && nj < c && ni >= 0 && nj >= 0){
            if (grid[ni][nj] == 0){
                if (!visEmpty.count({ni, nj})){
                    visEmpty.insert({ni, nj});
                    freq++;
                }
            }
            else if (grid[ni][nj] == 1 && !vis[ni][nj]){ dfs(ni, nj, idx, freq, grid, vis, visEmpty); }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ifstream cin("in.txt");
    ofstream cout("out.txt");

    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cin >> r >> c;
        vector<vector<int>> grid(r, vector<int>(c, 0));
        for(int i = 0; i < r; i++){
            string s; cin >> s;
            for(int j = 0; j < c; j++){
                if (s[j] == 'W') { grid[i][j] = 1; }
                else if (s[j] == 'B') { grid[i][j] = 2; }
            }
        }

        vector<vector<bool>> vis(r, vector<bool>(c, false));
        int idx = 0, freq = 0; bool OK = false;
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                if (!vis[i][j] && grid[i][j] == 1){
                    set<pair<int, int>> visEmpty; freq = 0;
                    idx++; dfs(i, j, idx, freq, grid, vis, visEmpty);
                    if (freq == 1){ OK = true; break; }
                }
            }
        }

        cout << "Case #" << qq << ": ";
        if (OK) { cout << "YES\n"; }
        else { cout << "NO\n"; }
    }
}