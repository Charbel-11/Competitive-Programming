#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll INF = 1e10;
struct Edge {
    int u, v; ll cap, cost, flow = 0; Edge() {}
    Edge(int _u, int _v, ll _cap, ll _cost) :
            u(_u), v(_v), cap(_cap), cost(_cost) {}
};
struct Graph {
    vector<vector<int>> nodes; int n;
    vector<Edge> edges; int m = 0; vector<ll> P;
    Graph(int _n) : n(_n), nodes(_n), P(_n) {}
    void addEdge(int u, int v, ll cost, ll cap1, ll cap2 = 0) {
        nodes[u].emplace_back(m++);
        nodes[v].emplace_back(m++);
        edges.emplace_back(u, v, cap1, cost);
        edges.emplace_back(v, u, cap2, -cost);
    }
    ll minCostFlow(int s, int t, int k, ll prevFlow = 0) {
        ll flow = prevFlow, newFlow = 0, cost = 0;
        vector<int> parent(n);
        while (flow < k && (newFlow = maxFlowDijkstra(s, t, parent))) {
            newFlow = min(newFlow, k - flow);
            flow += newFlow; int cur = t;
            while (cur != s) {
                int& e = parent[cur]; cost += edges[e].cost * newFlow;
                edges[e].cap -= newFlow; edges[e ^ 1].cap += newFlow;
                edges[e].flow += newFlow; edges[e ^ 1].flow -= newFlow;
                cur = edges[e].u;
            }
        }
        return flow == k ? cost : -1;
    }
    ll maxFlowDijkstra(const int& s, int t, vector<int>& parent) {
        vector<ll> dist(n, INF); dist[s] = 0ll;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        pq.push({ 0, s }); vector<bool> vis(n, false);
        while (!pq.empty()) {
            if (vis[pq.top().second]) { pq.pop(); continue; }
            int cur = pq.top().second; pq.pop(); vis[cur] = true;
            for (auto& e : nodes[cur]) if(edges[e].cap > 0) {
                    int v = edges[e].v; ll W = edges[e].cost + P[cur] - P[v];
                    if (dist[v] > dist[cur] + W) {
                        parent[v] = e; dist[v] = dist[cur] + W;
                        pq.push({ dist[v], v });
                    }
                }
        }
        for (int i = 0; i < n; i++) P[i] += dist[i];
        if (dist[t] == INF) { return 0; }
        ll res = INF; while (t != s) {
            int e = parent[t]; res = min(res, edges[e].cap); t=edges[e].u;
        }
        return res;
    }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, k; cin >> n >> k;
    Graph g(k + 2*n + 2);

    int src = k+2*n; int sink = src+1;
    for(int j = 0; j < n; j++){
        int w; cin >> w;
        for(int d = 0; d < k; d++) {
            g.addEdge(d, k + 2 * j, w, 1);
        }
    }
    for(int i = 0; i < n; i++){
        int curOut = k + 2 * i + 1;
        for(int curIn = curOut + 1; curIn < k + 2*n; curIn += 2){
            int w; cin >> w;
            g.addEdge(curOut, curIn, w, 1);
        }
    }

    for(int i = 0; i < k; i++){ g.addEdge(src, i, 0, 1); }
    for(int i = k + 1; i < k + 2*n; i += 2){ g.addEdge(src, i, 0, 1); }
    for(int i = k; i < k + 2*n; i += 2){ g.addEdge(i, sink, 0, 1); }

    cout << g.minCostFlow(src, sink, n) << '\n';
}

