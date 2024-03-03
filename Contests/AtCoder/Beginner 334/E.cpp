#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
    ll res = 1; x %= mod;
    for (; p; p >>= 1, x = (x * x) % mod) {
        if (p & 1) { res = (res * x) % mod; }
    }
    return res;
}
// mod must be prime
ll modInv(ll i) { return powe(i, mod - 2); }

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int h, w; cin >> h >> w;
    vector<vector<ll>> grid(h, vector<ll>(w, -1));
    for(int i = 0; i < h; i++){
        string s; cin >> s;
        for(int j = 0; j < w; j++){
            if (s[j] == '#'){
                grid[i][j] = 0;
            }
        }
    }

    function<void(int, int, ll)> dfs = [&](int i, int j, ll idx) -> void{
        grid[i][j] = idx;
        for(int k = 0; k < 4; k++){
            int ni = i + dx[k], nj = j + dy[k];
            if (ni >= 0 && nj >= 0 && ni < h && nj < w){
                if (grid[ni][nj] == 0){
                    dfs(ni, nj, idx);
                }
            }
        }
    };

    ll numRed = 0, color = 0;
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            if (grid[i][j] == -1){ numRed++; }
            else if (grid[i][j] != 0){ continue; }
            else{ dfs(i, j, ++color); }
        }
    }

    ll ans = 0;
    for(int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == -1){
                set<ll> neighboringComponents;
                for(int k = 0; k < 4; k++) {
                    int ni = i + dx[k], nj = j + dy[k];
                    if (ni >= 0 && nj >= 0 && ni < h && nj < w) {
                        if (grid[ni][nj] != -1){ neighboringComponents.insert(grid[ni][nj]); }
                    }
                }
                ans += color - (ll)neighboringComponents.size() + 1;
                ans %= mod;
            }
        }
    }
    ans *= modInv(numRed); ans %= mod;
    cout << ans << '\n';
}

