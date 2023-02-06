#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 1ll << 60;

struct edge {
    int u, v; ll w; edge() {}
    edge(int _u, int _v, ll _w) :
            u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct graph {
    vector<node> nodes; int n;
    vector<ll> dist;
    graph(int _n) : n(_n) { nodes.resize(n); dist.resize(n, INF); }

    void add_edge(int u, int v, ll w) {
        edge e1(u, v, w);
        nodes[u].edges.push_back(e1);
    }

    void dijkstra_sp(int s, vector<int> &parent) {
        vector<bool> visited(n, false);
        priority_queue <pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        dist[s] = 0ll; pq.push({ 0, s });

        while(!pq.empty()) {
            int cur = pq.top().second; pq.pop();
            if (visited[cur]) { continue; }
            visited[cur] = true;

            for (auto &e : nodes[cur].edges)
                if (dist[e.v] > dist[cur] + e.w) {
                    dist[e.v] = dist[cur] + e.w;
                    parent[e.v] = e.u;
                    pq.push({ dist[e.v], e.v });
                }
        }
    }
};

int usualDx[] = {0, 0, 1, -1};
int usualDy[] = {-1, 1, 0, 0};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
        int n, m; cin >> n >> m;
        vector<string> grid(n);
        for(auto &s : grid){ cin >> s; }

        auto idx = [&](int i, int j){ return i*m + j; };

        vector<bool> canUse(n*m);
        for(int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                bool OK = true;
                for(int k = 0; k < 4; k++){
                    int ni = i + usualDx[k], nj = j + usualDy[k];
                    if (ni < 0 || nj < 0 || ni >= n || nj >= m){ continue; }
                    if (grid[ni][nj] == '#'){ OK = false; break; }
                }
                canUse[idx(i, j)] = OK;
            }
        }

        graph g(n*m+2); int src = n*m, dest = n*m+1;
        for(int i = 0; i < n; i++){
            if (canUse[idx(i, 0)]){ g.add_edge(src, idx(i, 0), grid[i][0] == '.'); }
            if (canUse[idx(i, m-1)]) { g.add_edge(idx(i, m-1), dest, 0); }
        }
        for(int i = 0; i < n; i++){
            for (int j = 0; j < m - 1; j++){
                if (!canUse[idx(i, j)]){ continue; }
                for (int ni : {i-1, i+1}){
                    int nj = j + 1;
                    if (ni < 0 || nj < 0 || ni >= n || nj >= m){ continue; }
                    if (canUse[idx(ni, nj)]) {
                        g.add_edge(idx(i, j), idx(ni, nj), grid[ni][nj] == '.');
                        g.add_edge(idx(ni, nj), idx(i, j), grid[i][j] == '.');
                    }
                }
            }
        }

        vector<int> parent(n*m+2, -1);
        g.dijkstra_sp(src, parent);

        if (parent[dest] == -1){ cout << "NO\n"; }
        else {
            cout << "YES\n";
            int cur = parent[dest];
            while(cur != src){
                int i = cur/m, j = cur%m;
                grid[i][j] = '#';
                cur = parent[cur];
            }

            for(auto &s : grid){
                cout << s << '\n';
            }
        }
    }
}