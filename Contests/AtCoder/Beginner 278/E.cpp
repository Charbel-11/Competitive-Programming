#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int H,W,N,h,w; cin >> H >> W>> N >> h >> w;
    vector<int> freq(N+1, 0); int distinct = 0;

    vector<vector<int>> grid(H, vector<int>(W));
    for(auto &v : grid){
        for(auto &x : v){
            cin >> x;
            freq[x]++;
            if (freq[x] == 1){ distinct++; }
        }
    }

    vector<vector<int>> ans(H-h + 1, vector<int>(W-w + 1));
    for(int i = 0; i <= H-h; i++){
        for(int ii = i; ii < i + h; ii++){
            for(int jj = 0; jj < w; jj++){
                freq[grid[ii][jj]]--;
                if (freq[grid[ii][jj]] == 0){ distinct--; }
            }
        }

        ans[i][0] = distinct;
        for(int j = 1; j <= W-w; j++){
            for(int k = i; k < i + h; k++){
                freq[grid[k][j-1]]++;
                if (freq[grid[k][j-1]] == 1){ distinct++; }

                freq[grid[k][j + w - 1]]--;
                if (freq[grid[k][j + w - 1]] == 0){ distinct--; }
            }
            ans[i][j] = distinct;
        }

        for(int j = W-w; j < W; j++){
            for(int k = i; k < i + h; k++) {
                freq[grid[k][j]]++;
                if (freq[grid[k][j]] == 1) { distinct++; }
            }
        }
    }

    for(auto &v : ans){
        for(auto &x : v){
            cout << x << ' ';
        }
        cout << '\n';
    }
}