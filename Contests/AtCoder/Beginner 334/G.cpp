#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

struct edge {
    int u, v, w; edge() {}
    edge(int _u, int _v, int _w) :
            u(_u), v(_v), w(_w) {}
};

struct node { vector<int> edges; };

struct graph {
    vector<int> compChange;
    vector<node> nodes; int n;
    vector<edge> edges;
    graph(int _n) : n(_n) { nodes.resize(n); compChange.resize(n, 1); }

    void add_edge(int u, int v, int w = 0) {
        nodes[u].edges.emplace_back(edges.size());
        edges.emplace_back(u, v, w);
    }

    void artPointDFS(int cur, int p, vector<bool> &vis, vector<int> &low, vector<int> &tin, int &timer) {
        vis[cur] = true; tin[cur] = low[cur] = timer++; int c = 0, comp = 1;
        for (auto &x : nodes[cur].edges) {
            edge &e = edges[x];	if (e.v == p) { continue; }
            if (vis[e.v]) { low[cur] = min(low[cur], tin[e.v]); continue; }

            artPointDFS(e.v, cur, vis, low, tin, timer);
            low[cur] = min(low[cur], low[e.v]); c++;
            if (p != -1 && low[e.v] >= tin[cur]){
                compChange[cur] = ++comp;
            }; //isArtPoint(cur);		Might run this for node cur multiple times (once for each child)
        }
        if (p == -1 && c > 1){
            compChange[cur] = c;
        } //isArtPoint(cur);
        else if (p == -1 && c == 0){ compChange[cur] = 0; }
    }
};

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
    vector<vector<ll>> grid(h, vector<ll>(w, 1));
    for(int i = 0; i < h; i++){
        string s; cin >> s;
        for(int j = 0; j < w; j++){
            if (s[j] == '#'){ grid[i][j] = 0; }
        }
    }

    graph g(h * w);
    ll numGreen = 0, ans = 0;
    for(int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == 0){
                numGreen++;
                int curNode = i * w + j;
                for(int k = 0; k < 4; k++) {
                    int ni = i + dx[k], nj = j + dy[k];
                    if (ni >= 0 && nj >= 0 && ni < h && nj < w) {
                        if (grid[ni][nj] == 0){
                            int curNeighb = ni * w + nj;
                            g.add_edge(curNode, curNeighb);
                        }
                    }
                }
            }
        }
    }

    int numComp = 0;
    vector<bool> vis(h*w, false);
    vector<int> low(h*w), tin(h*w);
    int time = 0;

    for(int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == 0 && !vis[i*w+j]) {
                numComp++;
                g.artPointDFS(i*w+j, -1, vis, low, tin, time);
            }
        }
    }

    for(int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == 0) {
                ans += numComp + g.compChange[i*w + j] - 1;
                ans %= mod;
            }
        }
    }

    ans *= modInv(numGreen); ans %= mod;
    cout << ans << '\n';
}

