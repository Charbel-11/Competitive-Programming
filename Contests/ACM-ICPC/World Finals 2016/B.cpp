#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 1 << 30;
struct edge {
	int u, v, w; edge() {}
	edge(int _u, int _v, int _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	vector<int> dist;
	graph(int _n) : n(_n) { nodes.resize(n); dist.resize(n, INF); }

	void add_edge(int u, int v, int w, bool directed) {
		edge e1(u, v, w);
		nodes[u].edges.push_back(e1);
		if (!directed) {
            edge e2(v, u, w);
            nodes[v].edges.push_back(e2);
        }
	}

	void dijkstra_sp(int s) {
		vector<bool> visited(n, false);
		priority_queue <pair<int, int>, vector<pair<int, int>>, greater<>> pq;
		dist[s] = 0; pq.push({ 0, s });

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
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

    int n, b, s, r; cin >> n >> b >> s >> r;
    graph g(n), gRev(n);
    for(int i = 0; i < r; i++){
        int u, v, l; cin >> u >> v >> l; u--; v--;
        g.add_edge(u, v, l, true);
        gRev.add_edge(v, u, l, true);
    }
    g.dijkstra_sp(b);
    gRev.dijkstra_sp(b);

    vector<ll> c(b);
    for(int i = 0; i < b; i++){
        c[i] = g.dist[i] + gRev.dist[i];
    }
    sort(c.begin(), c.end());

    vector<ll> dp(b); ll curSum = 0;
    for(int i = 0; i < b; i++){
        curSum += c[i];
        dp[i] = curSum * i;
    }

    for(int j = 2; j <= s; j++){
        for(int i = b - 1; i >= j - 1; i--){
            curSum = 0; ll curCnt = 0;
            for(int k = i; k >= max(1, i-(i+1)/j); k--){
                curSum += c[k]; curCnt++;
                dp[i] = min(dp[i], dp[k-1] + curSum*(curCnt-1));
            }
        }
    }

    cout << dp[b-1] << '\n';
}