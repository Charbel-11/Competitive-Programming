#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int r, c;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void dfs(int i, int j, int& size, int& freq,
         const vector<vector<int>>& grid, vector<vector<bool>>& vis, set<pair<int, int>>& visEmpty){
    assert(vis.size() > i);
    vis[i][j] = true;
    size++;
    for(int k = 0; k < 4; k++){
        int ni = i + dx[k], nj = j + dy[k];
        if (ni < r && nj < c && ni >= 0 && nj >= 0){
            if (grid[ni][nj] == 0){
                if (!visEmpty.count({ni, nj})){
                    visEmpty.insert({ni, nj});
                    freq++;
                }
            }
            else if (grid[ni][nj] == 1 && !vis[ni][nj]){
                dfs(ni, nj, size, freq, grid, vis, visEmpty);
            }
        }
    }
}

void main_() {
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

        vector<vector<bool>> vis(r + 1, vector<bool>(c + 1, false));
        map<pair<int, int>, int> cnt;
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                if (!vis[i][j] && grid[i][j] == 1){
                    int freq = 0, size = 0;
                    set<pair<int, int>> visEmpty;
                    dfs(i, j, size, freq, grid, vis, visEmpty);
                    if (freq == 1){
                        cnt[*visEmpty.begin()] += size;
                    }
                }
            }
        }

        int ans = 0;
        for(auto &p : cnt){
            ans = max(ans, p.second);
        }
        cout << "Case #" << qq << ": " << ans << '\n';
    }
}

static void run_with_stack_size(void (*func)(void), size_t stsize) {
    char *stack, *send;
    stack = (char *)malloc(stsize);
    send = stack + stsize - 16;
    send = (char *)((uintptr_t)send / 16 * 16);
    asm volatile(
            "mov %%rsp, (%0)\n"
            "mov %0, %%rsp\n"
            :
            : "r"(send));
    func();
    asm volatile("mov (%0), %%rsp\n" : : "r"(send));
    free(stack);
}
int main() {
    run_with_stack_size(main_, 1024 * 1024 * 1024); // run with a 1 GiB stack
    return 0;
}