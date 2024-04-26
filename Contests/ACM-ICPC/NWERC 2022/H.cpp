#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int ans = 0;
vector<vector<int>> nodesAtDepth;
struct edge {
    int u, v; edge() {}
    edge(int _u, int _v) :
            u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
    vector<node> nodes;
    int root, n;

    tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); nodesAtDepth.resize(n); }

    void add_edge(int u, int v) {
        edge e1(u, v), e2(v, u);
        nodes[u].edges.push_back(e1);
        nodes[v].edges.push_back(e2);
    }

    int dfs(int u, int p, int curDepth, int& ts){
        int curTS = ts++; vector<int> childrenDepth;

        for(auto &e : nodes[u].edges){
            if (e.v == p){ continue; }
            int childDepth = dfs(e.v, u, curDepth + 1, ts);
            childrenDepth.push_back(childDepth);
        }

        while(childrenDepth.size() < 2){ childrenDepth.push_back(curDepth); }
        sort(childrenDepth.begin(), childrenDepth.end());

        if (childrenDepth[1] > childrenDepth[0] + 1){
            for(int i = childrenDepth[0] + 2; i <= childrenDepth[1]; i++){
                while(!nodesAtDepth[i].empty() && nodesAtDepth[i].back() > curTS){
                    ans++; nodesAtDepth[i].pop_back();
                }
            }
            childrenDepth[1] = childrenDepth[0] + 1;
        }

        nodesAtDepth[curDepth].push_back(curTS);
        return childrenDepth[1];
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n; cin >> n; tree t(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        t.add_edge(u, v);
    }

    int ts; t.dfs(0, -1, 0, ts);
    cout << ans << '\n';
}