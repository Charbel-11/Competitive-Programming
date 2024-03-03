#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct edge {
	int u, v; ll w; edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct Tree {
	vector<node> nodes; int n;
    vector<int> sz; vector<bool> dead;

	Tree(int _n) : n(_n) {
        nodes.resize(n); sz.resize(n, 1);
        dead.resize(n, false);
    }

	void add_edge(int u, int v, ll w = 1ll) {
		edge e1(u, v, w); edge e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	Tree build_CDT() {
		Tree CDT(n);
        dead.clear(); dead.resize(n, false);
        CDUtil(0, -1, CDT);
		return CDT;
	}

    void centroidDecomposition() { CDRec(0); }

    void getSize(int u, int p) {
        sz[u] = 1;
        for (auto& e : nodes[u].edges) {
            if (e.v == p || dead[e.v]) { continue; }
            getSize(e.v, u); sz[u] += sz[e.v];
        }
    }
    int getCentroid(int u, int p, int subtreeN) {
        for (auto e : nodes[u].edges) {
            if (e.v == p || dead[e.v]) { continue; }
            if (sz[e.v] > subtreeN / 2) { return getCentroid(e.v, u, subtreeN); }
        }
        return u;
    }

    void CDRec(int start) {
        getSize(start, -1);
        int c = getCentroid(start, -1, sz[start]);
        dead[c] = true;

        //Modify here
        dfs(c, -1, 0, false);
        for (auto& e : nodes[c].edges) {
            if (dead[e.v]) { continue; }
            dfs(e.v, c, 1, 1);
            addNeeded(e.v, c, 1);
        }

        for (auto& e : nodes[c].edges) {
            if (!dead[e.v]) { CDRec(e.v); }
        }
    }
    // to enable/disable subtree
    void dfs(int u, int p, int level, bool dir) {
        // add/rem cur node (according to dir)
        for (auto& e : nodes[u].edges) {
            if (e.v == p || dead[e.v]) { continue; }
            dfs(e.v, u, level + 1, dir);
        }
    }
    // to add contribution of a subtree with other subtrees
	void addNeeded(int u, int p, int level) {
        //same as dfs
    }

	//Builds the centroid tree (not needed for counting)
	void CDUtil(int start, int parent, Tree &CDT) {
        getSize(start, -1);
        int c = getCentroid(start, -1, sz[start]);
        if (parent != -1) { CDT.add_edge(c, parent); }
		else { CDT.root = c; }

		dead[c] = true;
		for (auto& e : nodes[c].edges) {
			if (dead[e.v]) { continue; }
			CDUtil(e.v, c, CDT);
		}
		dead[c] = false;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

}