#include <bits/stdc++.h>
using namespace std;

struct edge {
    int u, v; edge() {}
    edge(int _u, int _v) :
            u(_u), v(_v) {}
};

struct node { vector<edge> edges1, edges; };

struct graph {
    vector<node> nodes; int n;
    graph(int _n) : n(_n) { nodes.resize(n); }

    void add_edge(int u, int v, int type) {
        edge e1(u, v);
        if (type == 1) { nodes[u].edges1.push_back(e1); }
        nodes[u].edges.push_back(e1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n; cin >> n; int idx = 0;
    map<string, int> m; map<int, string> m2;
    vector<pair<pair<int, int>, int>> edges;
    for(int i = 0; i < n; i++){
        string s1, t, s2; cin >> s1 >> t >> s2;
        if (!m.count(s1)){ m2[idx] = s1; m[s1] = idx++; }
        if (!m.count(s2)) { m2[idx] = s2; m[s2] = idx++; }
        if (t == "??") {
            edges.push_back({{m[s2], m[s1]}, 2});
            edges.push_back({{m[s1], m[s2]}, 2});
        }
        else{
            edges.push_back({{m[s1], m[s2]}, 1});
        }
    }

    n = idx; graph G(n);
    set<int> inS0; stack<int> S0, S;
    for(auto &p2 : edges){
        int u = p2.first.first, v = p2.first.second, type = p2.second;
        G.add_edge(u, v, type);
        if (type == 1 && !inS0.count(u)){ S0.push(u); inS0.insert(u); }
    }

    vector<bool> vis(n, false), possibleStart(n, true);
    vector<int> parent(n, -1);
    while(!S0.empty()){
        int u = S0.top(); S0.pop();
        for(auto &e : G.nodes[u].edges1){
            assert(!vis[e.v]);
            possibleStart[e.v] = false;
            vis[e.v] = true;
            S.push(e.v);
            parent[e.v] = e.u;
        }
    }

    vis.clear(); vis.resize(n, false);
    while(!S.empty()){
        int u = S.top(); S.pop();
        for(auto &e : G.nodes[u].edges){
            if (parent[e.u] == e.v){ continue; }
            assert(parent[e.v] == -1 || parent[e.v] == e.u);
            possibleStart[e.v] = false;
            if (!vis[e.v]){
                vis[e.v] = true;
                S.push(e.v);
                parent[e.v] = e.u;
            }
        }
    }

    vector<string> ans;
    for(int i = 0; i < n; i++){
        if (possibleStart[i]){
            ans.push_back(m2[i]);
        }
    }

    sort(ans.begin(), ans.end());
    for(auto &s : ans){ cout << s << '\n'; }
}