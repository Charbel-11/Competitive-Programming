#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e17;

struct BipartiteGraph {
    vector<vector<int>> nodes; int n, m; vector<int> level, match;
    BipartiteGraph(int _n, int _m) : n(_n), m(_m),
                                     nodes(_n+_m+1), level(_n + _m + 1), match(_n + _m + 1, 0) {}
    void addEdge(int u, int v) { // u in [0,n-1], v in [n,n+m]
        nodes[u+1].emplace_back(v+1); nodes[v+1].emplace_back(u+1);
    }
    bool matchingBFS() {
        fill(level.begin(), level.end(), -1);
        queue<int> q; for (int i = 1; i <= n; i++)
            if (!match[i]) { level[i] = 0; q.push(i); }
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            if (!cur) { continue; }
            for (auto &e : nodes[cur]) {
                if (level[match[e]] == -1) {
                    level[match[e]] = level[cur] + 1; q.push(match[e]);
                }
            }
        }
        return (level[0] != -1);
    }
    bool matchingDFS(int cur) {
        if (!cur) { return true; }
        if (cur) {
            for (auto &e : nodes[cur]) {
                if (level[match[e]] != level[cur] + 1) { continue; }
                if (!matchingDFS(match[e])) { continue; }
                match[e] = cur; match[cur] = e; return true;
            }
            level[cur] = INF; return false;
        }
        return true;
    }
    int hopcroftKarp() {
        int res = 0; while (matchingBFS())
            for (int i = 1; i <= n; i++)
                res += (match[i] == 0 && matchingDFS(i));
        return res;
    }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int r, c; cin >> r >> c;
    vector<vector<ll>> grid(r, vector<ll>(c));
    for(auto &v : grid)
        for(auto &x : v)
            cin >> x;


    ll ans = 0;
    vector<ll> rowMax(r, 0), colMax(c, 0);
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if (grid[i][j] == 0){ continue; }
            rowMax[i] = max(rowMax[i], grid[i][j] - 1);
            colMax[j] = max(colMax[j], grid[i][j] - 1);
            ans += grid[i][j] - 1;
        }
    }

    for(int i = 0; i < r; i++){ ans -= rowMax[i]; }
    for(int i = 0; i < c; i++){ ans -= colMax[i]; }

    BipartiteGraph G(r, c);
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if (rowMax[i] == colMax[j] && grid[i][j] > 0){
                G.addEdge(i, r + j);
            }
        }
    }

    int maxM = G.hopcroftKarp();
    for(int i = 1; i <= r; i++){
        if (G.match[i] != 0) { ans += rowMax[i-1]; }
    }

    cout << ans << '\n';
}

