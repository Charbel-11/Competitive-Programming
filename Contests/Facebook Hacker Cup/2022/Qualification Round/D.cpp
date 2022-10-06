#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct edge {
    int u, v; ll w; edge() {}
    edge(int _u, int _v, ll _w = 1) :
            u(_u), v(_v), w(_w) {}

    bool operator <(const edge& rhs){
        return v < rhs.v;
    }
};

struct node { vector<edge> edges; };

struct graph {
    vector<node> nodes;
    vector<unordered_map<int, ll>> ans;
    int n;

    graph(int _n) : n(_n) { nodes.resize(n); ans.resize(n); }

    void add_edge(int u, int v, ll c) {
        edge e1(u, v, c); nodes[u].edges.push_back(e1);
        edge e2(v, u, c); nodes[v].edges.push_back(e2);
    }

    void addSingleEdgeContribution(){
        for(int i = 0; i < n; i++){
            for(auto &e : nodes[i].edges){
                ans[i][e.v] += e.w * 2;
            }
        }
    }

    void findAllAnswers(int u){
        for(auto &e : nodes[u].edges){
            for(auto &e2 : nodes[e.v].edges){
                if (e.u == e2.v){ continue; }
                ll curAns = min(e.w, e2.w);
                ans[e.u][e2.v] += curAns;
            }
        }
    }

    ll getAns(int u, int v){
        int i = 0, j = 0; ll ans = 0;
        while(j < nodes[v].edges.size() && i < nodes[u].edges.size()){
            auto &e1 = nodes[u].edges[i];
            auto &e2 = nodes[v].edges[j];
            if (e1.v == e2.v){
                ans += min(e1.w, e2.w);
                i++; j++;
            }
            else if (e1.v < e2.v){
                i++;
            }
            else{
                j++;
            }
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ifstream ifs("in.txt");
    ofstream ofs("out.txt");

    int t; ifs >> t;
    for (int qq = 1; qq <= t; qq++) {
        ofs << "Case #" << qq << ": ";
        int n, m, q; ifs >> n >> m >> q;
        graph g(n);
        for(int i = 0; i < m; i++) {
            int u, v; ll c; ifs >> u >> v >> c; u--; v--;
            g.add_edge(u, v, c);
        }

        int threshold = sqrt(m);

        g.addSingleEdgeContribution();
        for(int i = 0; i < n; i++){
            sort(g.nodes[i].edges.begin(), g.nodes[i].edges.end());
            if (g.nodes[i].edges.size() > threshold){
                g.findAllAnswers(i);
            }
        }

        while(q--){
            int u, v; ifs >> u >> v; u--; v--;
            if (g.nodes[u].edges.size() < g.nodes[v].edges.size()){
                swap(u, v);
            }

            if (g.nodes[u].edges.size() > threshold){
                ofs << g.ans[u][v] << ' ';
            }
            else{
                ofs << g.ans[u][v] + g.getAns(u, v) << ' ';
            }
        }

        ofs << '\n';
    }
}