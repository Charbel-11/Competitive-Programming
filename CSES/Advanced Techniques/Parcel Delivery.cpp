#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll INF = 1ll << 50;

struct Edge {
    ll cap, cost, flow = 0;
    int u, v; Edge() {}
    Edge(int _u, int _v, ll _cap, ll _cost) :
            u(_u), v(_v), cap(_cap), cost(_cost) {}
};

struct Graph {
    vector<vector<int>> nodes;
    vector<Edge> edges;
    int n, m = 0;

    Graph(int _n) : n(_n), nodes(_n) {}

    void addEdge(int u, int v, ll cost, ll cap1, ll cap2 = 0) {
        nodes[u].emplace_back(m++);
        nodes[v].emplace_back(m++);
        edges.emplace_back(u, v, cap1, cost);
        edges.emplace_back(v, u, cap2, -cost);
    }

    // Runs in O(n^2.m^2)
    // Returns the min-cost to get a flow of k from s to t (or INF if it is impossible)
    // We can remove k to solve the min-cost max-flow problem (finds max flow and minimizes cost for that max flow)
    ll minCostFlow(int s, int t, ll k) {
        ll flow = 0, cost = 0;
        vector<int> parent(n);
        ll newFlow = maxFlowBellmanFord(s, t, parent);

        while (flow < k && newFlow > 0) {
            newFlow = min(newFlow, k - flow);
            flow += newFlow; int cur = t;
            while (cur != s) {
                int& e = parent[cur]; cost += edges[e].cost * newFlow;
                edges[e].cap -= newFlow; edges[e ^ 1].cap += newFlow;
                edges[e].flow += newFlow; edges[e ^ 1].flow -= newFlow;
                cur = edges[e].u;
            }
            newFlow = maxFlowBellmanFord(s, t, parent);
        }
        return flow == k ? cost : INF;
    }

    // Finds the shortest path (w.r.t. costs) and adds as much flow as possible along this path
    // Assumes there is no negative-weight cycle of costs
    ll maxFlowBellmanFord(const int& s, int t, vector<int>& parent) {
        parent.assign(n, -1); parent[s] = -2;
        vector<ll> dist(n, INF); dist[s] = 0;
        vector<bool> inQueue(n, false);
        queue<int> q; q.push(s);

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            inQueue[cur] = false;

            for (auto& e : nodes[cur]) {
                int u = edges[e].u, v = edges[e].v;
                if (edges[e].cap && dist[v] > dist[u] + edges[e].cost) {
                    parent[v] = e; dist[v] = dist[u] + edges[e].cost;
                    if (!inQueue[v]) { q.push(v); inQueue[v] = true; }
                }
            }
        }

        if (dist[t] == INF) { return 0; }
        ll res = INF; int cur = t;
        while (cur != s) {
            int e = parent[cur];
            res = min(res, edges[e].cap);
            cur = edges[e].u;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, k; cin >> n >> m >> k;
    Graph g(n);
    for(int i = 0; i < m; i++){
        int u, v; cin >> u >> v; u--;v--;
        int r, c; cin >> r >> c;
        g.addEdge(u, v, c, r);
    }

    ll ans = g.minCostFlow(0, n-1, k);
    if (ans == INF) { cout << -1 << '\n'; }
    else { cout << ans << '\n'; }
}