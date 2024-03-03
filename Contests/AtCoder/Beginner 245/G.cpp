#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
typedef long long ll;

vector<int> nations;
vector<bool> popular;

struct edge {
    int u, v; ll w; edge() {}
    edge(int _u, int _v, ll _w) :
            u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct pqNode{
    int nodeIdx, nation;
    ll distance;
    pqNode(int _nation, int _nodeIdx, ll _dist): nation(_nation), nodeIdx(_nodeIdx), distance(_dist) {}

    bool operator>(const pqNode& rhs) const{
        return distance > rhs.distance;
    }
};

struct graph {
    vector<node> nodes; int n;
    vector<vector<pair<ll, int>>> dist;
    graph(int _n) : n(_n) { nodes.resize(n); dist.resize(n); }

    //UNDIRECTED
    void add_edge(int u, int v, ll w) {
        edge e1(u, v, w), e2(v, u, w);
        nodes[u].edges.push_back(e1);
        nodes[v].edges.push_back(e2);
    }

    void dijkstra_sp() {
        vector<bool> visited(n, false);
        priority_queue <pqNode, vector<pqNode>, greater<pqNode>> pq;
        for(int i = 0; i < n; i++){
            if (popular[i]){
                pq.push(pqNode(nations[i], i, 0));
            }
        }

        while(!pq.empty()) {
            auto curPQNode = pq.top(); pq.pop();
            int curNode = curPQNode.nodeIdx, curNation= curPQNode.nation;
            ll curDist = curPQNode.distance;

            if (dist[curNode].size() == 2){ continue; }
            else if (dist[curNode].size() == 1){
                if (dist[curNode][0].second != curNation) {
                    dist[curNode].push_back({curDist, curNation});
                }
                else { continue; }
            }
            else {
                dist[curNode].push_back({curDist, curNation});
            }

            for (auto &e : nodes[curNode].edges)
                pq.push(pqNode{ curNation, e.v, curDist + e.w});
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n,m, k,l; cin >> n >> m >> k >> l;
    graph g(n);
    nations.resize(n); for(auto &x : nations){cin>>x;}
    popular.resize(n, false);
    for(int i = 0; i < l; i++){
        int cur; cin >> cur; cur--;
        popular[cur] = true;
    }
    for(int i = 0; i < m; i++){
        int u,v; cin >> u >> v; u--; v--;
        ll w; cin >> w;
        g.add_edge(u, v, w);
    }

    g.dijkstra_sp();
    for(int i = 0; i < n; i++){
        if (g.dist[i].size() > 0 && g.dist[i][0].second != nations[i]){
            cout << g.dist[i][0].first << ' ';
        }
        else if (g.dist[i].size() > 1){
            cout << g.dist[i][1].first << ' ';
        }
        else {
            cout << -1 << ' ';
        }
    }
}