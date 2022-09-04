#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m;
int dx[] = {-1, 1, 0, 0, 0};
int dy[] = {0, 0, -1, 1, 0};

bool isBad(vector<vector<int>>& grid, int i, int j){
    if (grid[i][j] == 1) { return false; }
    for(int k = 0; k < 4; k++){
        int ni = i + dx[k], nj = j + dy[k];
        if (ni >=0 && nj >= 0 && ni < n && nj < m){
            if (grid[i][j] > grid[ni][nj]) {
                return false;
            }
        }
    }
    return true;
}

bool hasNoBadPairsAfterSwap(vector<vector<bool>>& prevBad, vector<vector<int>>&grid, pair<int, int> p1, pair<int, int> p2, int numBad){
    set<pair<int, int>> candidates;
    for(auto p : {p1, p2}) {
        int i = p.first, j = p.second;
        for (int k = 0; k < 5; k++) {
            int curI = i + dx[k], curJ = j + dy[k];
            if (curI >=0 && curJ >= 0 && curI < n && curJ < m) {
                candidates.insert({curI, curJ});
            }
        }
    }

    for(auto &p : candidates){
        int i = p.first, j = p.second;
        bool nowBad = isBad(grid, i, j);
        if (nowBad) { return false; }
        if (prevBad[i][j]){ numBad--; }
    }
    return numBad == 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for(auto &v : grid){
        for(auto &x : v){
            cin >> x;
        }
    }

    pair<int, int> badPair = {-1, -1};
    vector<vector<bool>> bad(n, vector<bool>(m));
    int numBad = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            bad[i][j] = isBad(grid, i, j);
            if (bad[i][j]){
                badPair = {i, j};
                numBad++;
            }
        }
    }

    if (badPair.first == -1){ cout << 0 << '\n'; return 0; }

    bool OK1 = false; int ans1 = 0;
    for(int k = 0; k < 5; k++){
        int curI = badPair.first + dx[k], curJ = badPair.second + dy[k];
        if (curI >=0 && curJ >= 0 && curI < n && curJ < m){
            for(int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    swap(grid[curI][curJ], grid[i][j]);
                    if (hasNoBadPairsAfterSwap(bad, grid, {curI, curJ}, {i, j}, numBad)) {
                        bool skip = false;
                        if (curI > i || (curI == i && curJ > j)) {
                            for (int kk = 0; kk < 5; kk++) {
                                int ni = badPair.first + dx[kk], nj = badPair.second + dy[kk];
                                if (ni == i && nj == j) {
                                    skip = true;
                                }
                            }
                        }

                        if (!skip) {
                            OK1 = true;
                            ans1++;
                        }
                    }
                    swap(grid[curI][curJ], grid[i][j]);
                }
            }
        }
    }

    if (OK1){
        cout << 1 << " " << ans1 << '\n';
    }
    else{
        cout << 2 << '\n';
    }
}