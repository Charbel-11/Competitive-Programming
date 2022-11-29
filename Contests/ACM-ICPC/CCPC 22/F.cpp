#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int c[302];
ll w[302];
ll ans[302][302];

struct edge {
    int u, v; edge() {}
    edge(int _u, int _v) :
            u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct compressedGraph{
    vector<vector<ll>> dist;
    int n;

    compressedGraph(int _n) : n(_n) { dist.resize(n, vector<ll>(n, 1e15)); }

    void getShortestPath(int u, vector<vector<ll>>& compD){
        vector<ll> minAlt(n, 1e15), curMinD(n, 1e15);
        for(int i = 0; i < n; i++){ ans[u][i] = 1e15; }

        curMinD[u] = 0;
        for(int i = 0; i < n; i++){
            int curU = -1;
            for(int j = 0; j < n; j++){
                if (minAlt[j] < 1e15){ continue; }
                if (curMinD[j] < 1e15){ curU = j; break; }
            }
            for(int j = curU + 1; j < n; j++){
                if (minAlt[j] < 1e15){ continue; }
                if (curMinD[j] < curMinD[curU]){ curU = j; }
            }

            if (curU == -1){ break; }

            minAlt[curU] = curMinD[curU];
            for(int curV = 0; curV < n; curV++){
                if (minAlt[curV] < 1e15 || dist[curU][curV] == 1e15){ continue; }
                curMinD[curV] = min(curMinD[curV], max(curMinD[curU], dist[curU][curV]));
            }
        }

        for(int j = 0; j < n; j++){
            ans[u][j] = min(ans[u][j], minAlt[j]);
            for(int k = 0; k < n; k++){
                if (c[j] == c[k])
                    ans[u][k] = min(ans[u][k], max(w[j] + compD[j][k], minAlt[j]));
            }
        }
    }
};

struct graph {
    vector<node> nodes;
    vector<vector<int>> comp;
    vector<vector<ll>> compD;
    vector<bool> vis;
    int n;

    graph(int _n) : n(_n) {
        nodes.resize(n); vis.resize(n, 0);
        compD.resize(n, vector<ll>(n, 1e15));
    }

    void add_edge(int u, int v) {
        edge e1(u, v); nodes[u].edges.push_back(e1);
        edge e2(v, u); nodes[v].edges.push_back(e2);
    }

    void dfs(int u, vector<int>& curComp){
        curComp.push_back(u); vis[u] = true;
        for(auto &e : nodes[u].edges){
            if(vis[e.v] || c[e.v] != c[e.u]){continue;}
            dfs(e.v, curComp);
        }
    }

    void getComp(){
        for(int i = 0; i < n; i++){
            if (vis[i]){ continue; }
            vector<int> curComp;
            dfs(i, curComp);
            comp.push_back(curComp);
        }
    }

    void getCompAPSP(){
        for(int i = 0; i < n; i++){
            compD[i][i] = 0;
            for(auto &e : nodes[i].edges){
                if (c[e.v] == c[i]){ compD[i][e.v] = w[e.v]; }
            }
        }

        for(auto &v : comp){
            int curN = v.size();
            for(int k = 0; k < curN; k++){
                for(int i = 0; i < curN; i++){
                    for(int j = 0; j < curN; j++){
                        compD[v[i]][v[j]] = min(compD[v[i]][v[j]], compD[v[i]][v[k]] + compD[v[k]][v[j]]);
                    }
                }
            }
        }
    }

    void buildCompressedGraph(compressedGraph& cG){
        for(auto &v : comp) {
            for(auto &i : v) {
                for (auto &j : v) {
                    for(auto &e : nodes[j].edges){
                        if(c[e.v] != c[i]) {
                            cG.dist[i][e.v] = min(cG.dist[i][e.v], w[i] + compD[i][j] + w[e.v]);
                        }
                    }
                }
            }
        }
    }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n, m; cin >> n >> m;
        graph g(n);

        for(int i = 0; i < n; i++){ cin >> c[i]; }
        for(int i = 0; i < n; i++){ cin >> w[i]; }

        for(int i = 0; i < m; i++){
            int u, v; cin >> u >> v; u--; v--;
            g.add_edge(u, v);
        }

        g.getComp();
        g.getCompAPSP();

        compressedGraph cG(n);
        g.buildCompressedGraph(cG);

        for(int i = 0; i < n; i++){
            cG.getShortestPath(i, g.compD);
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cout << ans[i][j] << ' ';
            }
            cout << '\n';
        }
	}
}
