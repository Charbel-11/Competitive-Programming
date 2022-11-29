#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int dx[] = {-1, 1};
int dy[] = {-1, 1};

int countBits(int x){
    int ans = 0;
    while(x){
        ans++; x = x&(x-1);
    }
    return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	vector<vector<int>> scores(5);
    scores[0].resize(3);
    scores[1].resize(4);
    scores[2].resize(5);
    scores[3].resize(4);
    scores[4].resize(3);

    for(auto &v : scores)
        for(auto &x : v)
            cin >> x;

    vector<vector<int>> indices = scores; int idx = 0;
    for(int i = 0; i < 5; i++){
        for(int & j : indices[i]){
            j = idx++;
        }
    }

    vector<int> dp((1<<19), 0);

    vector<int> masks;
    for(int m = 3; m < (1<<19); m++) {
        masks.push_back(m);
    }
    sort(masks.begin(), masks.end(), [](int& lhs, int& rhs){
        return countBits(lhs) < countBits(rhs);
    });

    for(auto &m : masks){
        vector<vector<int>> grid = scores;
        for(int i = 0; i < 5; i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                grid[i][j] = ((m >> indices[i][j]) & 1);
            }
        }

        for(int i = 0; i < 5; i++){
            for(int j = 0; j < grid[i].size(); j++){
                if (!grid[i][j]){ continue; }

                dp[m] = max(dp[m], dp[m ^ (1 << indices[i][j])]);

                for(int k : dx){
                    int nj = j + k, nj2 = j + 2 * k;
                    if (nj2 < 0 || nj2 >= grid[i].size() || grid[i][nj2] || !grid[i][nj]){ continue; }
                    int newM = m ^ (1 << indices[i][j]) ^ (1 << indices[i][nj]) ^ (1 << indices[i][nj2]);
                    dp[m] = max(dp[m], dp[newM] + scores[i][nj]);
                }

                for(int ky : dy){
                    int ni = i + ky, ni2 = i + 2 * ky;
                    if (ni2 < 0 || ni2 >= 5){ continue; }

                    int nj = j, nj2 = j;
                    if (grid[ni].size() < grid[i].size()) {
                        nj--; nj2--;
                    }
                    if (grid[ni2].size() < grid[ni].size()){
                        nj2--;
                    }
                    if (nj2 >= 0 && grid[ni][nj] && !grid[ni2][nj2]){
                        int newM = m ^ (1 << indices[i][j]) ^ (1 << indices[ni][nj]) ^ (1 << indices[ni2][nj2]);
                        dp[m] = max(dp[m], dp[newM] + scores[ni][nj]);
                    }

                    nj = j; nj2 = j;
                    if (grid[ni].size() > grid[i].size()) {
                        nj++; nj2++;
                    }
                    if (grid[ni2].size() > grid[ni].size()){
                        nj2++;
                    }
                    if (nj2 < grid[ni2].size() && grid[ni][nj] && !grid[ni2][nj2]){
                        int newM = m ^ (1 << indices[i][j]) ^ (1 << indices[ni][nj]) ^ (1 << indices[ni2][nj2]);
                        dp[m] = max(dp[m], dp[newM] + scores[ni][nj]);
                    }
                }
            }
        }
    }

    int n; cin >> n;
    while(n--){
        int curState = 0;
        for(int i = 0; i < 5; i++) {
            string s; cin >> s;
            for (int j = 0; j < indices[i].size(); j++) {
                if(s[j] == '#'){
                    curState |= (1<<indices[i][j]);
                }
            }
        }

        cout << dp[curState] << '\n';
    }
}