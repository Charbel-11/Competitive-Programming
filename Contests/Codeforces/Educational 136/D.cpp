#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct edge {
    int u, v; edge() {}
    edge(int _u, int _v) :
            u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
    vector<node> nodes;
    int root, n;

    tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

    void add_edge(int u, int v) {
        edge e1(u, v), e2(v, u);
        nodes[u].edges.push_back(e1);
        nodes[v].edges.push_back(e2);
    }

    int dfs(int u, int p, int depth, int& cutsNeeded, int maxHeight){
        int curHeight = 0;
        for(auto &e : nodes[u].edges){
            if (e.v == p){ continue; }
            int childHeight = dfs(e.v, u, depth+1, cutsNeeded, maxHeight);
            curHeight = max(curHeight, childHeight);
        }
        curHeight++;

        if (depth <= 1){ return 0; }
        if (curHeight == maxHeight){ cutsNeeded++; return 0; }
        return curHeight;
    }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n, k; cin >> n >> k;
        tree tr(n);
        for(int i = 1; i < n; i++){
            int p; cin >> p; p--;
            tr.add_edge(i, p);
        }

        int l = 1, r = n-1;
        while(l < r){
            int mid = (l+r)/2;
            int cutsNeeded = 0;
            tr.dfs(0, -1, 0, cutsNeeded, mid);
            if (cutsNeeded <= k){ r = mid; }
            else { l = mid + 1; }
        }

        cout << l << '\n';
	}
}