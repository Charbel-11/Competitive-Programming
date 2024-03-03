#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct edge {
    int u, v, id; ll w; edge() {}
    edge(int _u, int _v, ll _w, int _id) :
            u(_u), v(_v), w(_w), id(_id) {}
};

struct node { vector<edge> edges; };

struct graph {
    vector<pair<int, ll>> starts;
    vector<node> nodes; int n, m = 0;
    graph(int _n) : n(_n) { nodes.resize(n); }

    void add_edge(int u, int v, ll w) {
        edge e1(u, v, w, m), e2(v, u, w, m);
        nodes[u].edges.push_back(e1);
        nodes[v].edges.push_back(e2);
        m++;
    }

    vector<ll> dijkstra_sp() {
        vector<ll> dist(n, 1e15);
        vector<bool> visited(n, false);
        priority_queue <pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        for(auto& p : starts){
            dist[p.first] = min(dist[p.first], p.second);
            pq.push({p.second, p.first});
        }

        while(!pq.empty()) {
            int cur = pq.top().second; pq.pop();
            if (visited[cur]) { continue; }
            visited[cur] = true;

            for (auto &e : nodes[cur].edges)
                if (dist[e.v] > dist[cur] + e.w) {
                    dist[e.v] = dist[cur] + e.w;
                    pq.push({ dist[e.v], e.v });
                }
        }
        return dist;
    }

    void generateAllCandidates(int rem, int cur, ll dist, set<int>& seenEdges){
        if (rem == 0){ starts.emplace_back(cur, dist); return; }
        for(auto &e : nodes[cur].edges){
            if (seenEdges.count(e.id)){ continue; }
            seenEdges.insert(e.id);
            generateAllCandidates(rem - 1, e.v, dist + e.w, seenEdges);
            seenEdges.erase(e.id);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, m; cin >> n >> m;
    graph g(n);
    for(int i = 0; i < m; i++){
        int u, v; ll w; cin >> u >> v >> w; u--; v--;
        g.add_edge(u, v, w);
    }

    set<int> seenEdges;
    g.generateAllCandidates(5, 0, 0, seenEdges);
    vector<ll> dist = g.dijkstra_sp();

    for(int i = 0; i < n; i++){
        cout << dist[i] << '\n';
    }
}