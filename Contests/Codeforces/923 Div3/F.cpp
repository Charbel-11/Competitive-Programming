#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct DSU {
    vector<int> rank, parent;

    DSU(int n) {
        rank.resize(n, 1); parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(const int u) {	return parent[u] == u ? u : (parent[u] = find(parent[u])); }
    int size(int u) { return rank[find(u)]; }

    bool connected(int u, int v){
        u = find(u); v = find(v);
        return u == v;
    }

    bool merge(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) { return false; }
        if (rank[u] < rank[v]) { swap(u, v); }
        rank[u] += rank[v];	parent[v] = u;
        return true;
    }
};

struct Edge {
    int u, v; int w; Edge() {}
    Edge(int _u, int _v, int _w = 1) :
            u(_u), v(_v), w(_w) {}

    bool operator<(const Edge& rhs){
        return w < rhs.w;
    }
};

struct Node { vector<Edge> edges; };

struct Graph {
    vector<int> parent;
    vector<Node> nodes;
    int n;

    Graph(int _n) : n(_n) { nodes.resize(n); parent.resize(n, -1); }

    void addEdge(int u, int v) {
        Edge e1(u, v); nodes[u].edges.push_back(e1);
        Edge e2(v, u); nodes[v].edges.push_back(e2);
    }

    void bfs(int start){
        vector<bool> visited(n, false);
        queue<int> Q;
        Q.push(start);

        while(!Q.empty()){
            int cur = Q.front(); Q.pop();
            for(auto &e : nodes[cur].edges){
                if (visited[e.v]){ continue; }
                visited[e.v] = true;
                parent[e.v] = e.u;
                Q.push(e.v);
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
        vector<Edge> edges;
        for(int i = 0; i < m; i++){
            int u, v, w; cin >> u >> v >> w; u--; v--;
            edges.emplace_back(u, v, w);
        }
        sort(edges.rbegin(), edges.rend());

        DSU dsu(n); int bestEdge = 0;
        for(int i = 0; i < m; i++){
            int u = edges[i].u, v = edges[i].v;
            if (dsu.connected(u, v)){ bestEdge = i; }
            dsu.merge(u, v);
        }

        Graph g(n);
        for(int i = 0; i < bestEdge; i++){
            g.addEdge(edges[i].u, edges[i].v);
        }
        g.bfs(edges[bestEdge].u);

        int cur = edges[bestEdge].v;
        vector<int> path; path.push_back(cur);
        while(cur != edges[bestEdge].u){
            cur = g.parent[cur];
            path.push_back(cur);
        }

        cout << edges[bestEdge].w << ' ' << path.size() << '\n';
        for(auto &x : path){ cout << x + 1 << ' '; }
        cout << '\n';
	}
}

