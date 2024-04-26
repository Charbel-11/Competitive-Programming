#include <bits/stdc++.h>
using namespace std;

struct edge {
    int u, v; edge() {}
    edge(int _u, int _v) :
            u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
    vector<node> nodes; int n;
    graph(int _n) : n(_n) { nodes.resize(n); }

    void addEdge(int u, int v) {
        edge e1(u, v); nodes[u].edges.push_back(e1);
    }

    void dfs(int u, vector<int> &visited, vector<int> &ans) {
        visited[u] = true;
        for (auto &e : nodes[u].edges) {
            int v = e.v;
            if (!visited[v]) { dfs(v, visited, ans); }
        }
        ans.push_back(u);
    }
    vector<int> topologicalSort() {
        vector<int> visited(n, false), ans;
        for (int i = 0; i < n; ++i)
            if (!visited[i]) { dfs(i, visited, ans); }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n, m; cin >> n >> m;
        vector<int> seq(m, -1);

        vector<vector<int>> ops;
        for(int i = 0; i < n; i++){
            int p; cin >> p;
            vector<int> curOps(p);
            for(auto& x : curOps){ cin >> x; x--; seq[x] = i; }
            ops.push_back(curOps);
        }

        graph g(n);
        for(int op = 0; op < n; op++){
            for(auto x : ops[op]){
                if(seq[x] == op){ continue; }
                g.addEdge(op, seq[x]);
            }
        }

        bool OK = false;
        auto topSort = g.topologicalSort();
        for(int i = 0; i < n; i++){
            if (topSort[i] != i){ OK = true; break; }
        }

        if (!OK){
            for(int i = 0; i < n - 1; i++){
                bool isConnected = false;
                for(auto& e : g.nodes[i].edges){
                    if (e.v == topSort[i+1]){
                        isConnected = true;
                        break;
                    }
                }
                if (!isConnected){
                    swap(topSort[i], topSort[i+1]);
                    OK = true;
                    break;
                }
            }
        }

        if (OK){
            cout << "Yes\n";
            for(auto x : topSort) { cout << x+1 << ' '; }
            cout << '\n';
        }
        else{
            cout << "No\n";
        }
	}
}

