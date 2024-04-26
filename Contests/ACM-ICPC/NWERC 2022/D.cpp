#include <bits/stdc++.h>
using namespace std;
typedef double ld;
const ld INF = 1ll << 60;
const ld PI = 3.14159265358979323846264338327950;

struct Edge {
    int u, v; ld w; Edge() {}
    Edge(int _u, int _v, ld _w) :
            u(_u), v(_v), w(_w) {}
};

struct Graph {
    vector<vector<Edge>> nodes; int n;
    Graph(int _n) : n(_n), nodes(_n) {}

    void addEdge(int u, int v, ld w) {
        nodes[u].emplace_back(u, v, w);
        nodes[v].emplace_back(v, u, w);
    }

    ld dijkstra(int s, int t) {
        vector<ld> dist(n, INF); dist[s] = 0ll;
        priority_queue<pair<ld, int>, vector<pair<ld, int>>, greater<pair<ld, int>>> pq;
        pq.push({ 0, s }); vector<bool> vis(n, false);

        while (!pq.empty()) {
            if (vis[pq.top().second]) { pq.pop(); continue; }
            int cur = pq.top().second; pq.pop(); vis[cur] = true;
            for (Edge &e : nodes[cur])
                if (dist[e.v] > dist[cur] + e.w) {
                    dist[e.v] = dist[cur] + e.w;
                    pq.push({ dist[e.v], e.v });
                }
        }
        return dist[t];
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int h, w; cin >> h >> w;
    int H = h << 1 | 1, W = w << 1 | 1;
    Graph G(H * W);
    vector<string> v(h); for(auto &s : v) cin >> s;

    for(int i = 0; i < H; ++i){
        for(int j = 0; j < W; ++j){
            if(i % 2 && j % 2) continue;

            int cur = i * W + j;
            int right = i * W + j + 1;
            int down = (i + 1) * W + j;
            int right_down = (i + 1) * W + j + 1;

            if(j + 1 != W && i % 2 == 0) G.addEdge(cur, right, 5);
            if(i + 1 != H && j % 2 == 0) G.addEdge(cur, down, 5);
            if((i % 2 ^ j % 2) && i + 1 != H && j + 1 != W && v[i / 2][j / 2] == 'O')
                G.addEdge(cur, right_down, 2.5 * PI);
        }
    }
    cout << fixed << setprecision(9) << G.dijkstra(0, H * W - 1) << '\n';
}