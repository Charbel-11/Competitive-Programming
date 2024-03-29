#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> base;

struct StVal {
	ll v = 0; StVal() {}
	StVal(const ll _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = v1 + v2; }
	operator ll() const { return v; }
};
struct SegTree {
	int n;
	vector<StVal> st;
	vector<int> leaves;

    SegTree() {}
	SegTree(const int n) : n(n) {
		leaves.resize(n);
		init(1, 0, n - 1);
	}

	//l, r indices of the actual array; si is the index of the segment tree array
	void init(const int si, const int l, const int r) {
		if (l == r) {
			if (si >= (int)st.size()) { st.resize(si + 1); }
			st[si] = StVal(base[l]);	//initialized with base
			leaves[l] = si;
			return;
		}

		int c1 = si << 1, c2 = (si << 1) | 1, mid = (l + r) >> 1;
		init(c1, l, mid); init(c2, mid + 1, r);
		st[si] = StVal(st[c1], st[c2]);
	}

	//l and r inclusive, 0-indexed
	StVal query(const int l, const int r) { return (l <= r && l < n && r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
	StVal query(const int l, const int r, const int si, const int lo, const int hi) {
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
	}

	//Sets arr[i] = c
	void update(const int i, ll c) {
		int si = leaves[i];
		st[si] = StVal(c);
		for (si >>= 1; si; si >>= 1)
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
	}
};

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};
struct node { ll val; vector<int> edges; };

struct tree {
    SegTree segT;
    vector<int> parent;
    vector<edge> edges;	vector<node> nodes;
    vector<int> depth, subtreeSize;
    vector<int> chainHead, chainIdx, posInBase;
    int root, n, chainNum, ptr;

    tree(int _n, int _r = 0) : n(_n), root(_r) {
        nodes.resize(n); parent.resize(n);
        depth.resize(n, 0); subtreeSize.resize(n, 1);
        chainNum = 0; ptr = 0; posInBase.resize(n);
        chainHead.resize(n, -1); chainIdx.resize(n);
    }

    void add_edge(int u, int v) {
        edge e1(u, v); edge e2(v, u);
        nodes[u].edges.push_back(edges.size()); edges.push_back(e1);
        nodes[v].edges.push_back(edges.size()); edges.push_back(e2);
    }

    void initializeHLD(){
        base.clear(); base.resize(n);

        dfsPre(0, -1);
        hld(0, -1);
        segT = SegTree(ptr);
    }

    void dfsPre(int u, int p) {
        for (auto &eIdx: nodes[u].edges) {
            auto &e = edges[eIdx];
            if (e.v == p) { continue; }
            depth[e.v] = depth[u] + 1;
            parent[e.v] = u;

            dfsPre(e.v, u);
            subtreeSize[u] += subtreeSize[e.v];
        }
    }

    void hld(int cur, int p) {
        if (chainHead[chainNum] == -1) { chainHead[chainNum] = cur; }
        chainIdx[cur] = chainNum;

        posInBase[cur] = ptr;	//sets the idx of the node in the segment tree array
        base[ptr++] = nodes[cur].val;		//sets the actual array

        int idx = -1, maxS = -1;
        for (auto &eIdx : nodes[cur].edges) {
            auto &e = edges[eIdx];
            if (e.v == p) { continue; }
            if (subtreeSize[e.v] > maxS) {
                maxS = subtreeSize[e.v];
                idx = e.v;
            }
        }

        if (idx >= 0) { hld(idx, cur); }

        for (auto &eIdx : nodes[cur].edges) {
            auto &e = edges[eIdx];
            if (e.v == p || e.v == idx) { continue; }
            chainNum++; hld(e.v, cur);
        }
    }

    //For node values
    void updateVal(int u, ll newVal) {
        segT.update(posInBase[u], newVal);
    }

    //O(log^2n)
    StVal query(int u, int v) {
        StVal res = StVal();
        int chainU = chainIdx[u], chainV = chainIdx[v];
        for(; chainU != chainV; v = parent[chainHead[chainV]], chainV = chainIdx[v]){
            if (depth[chainHead[u]] > depth[chainHead[v]]) { swap(u, v); swap(chainU, chainV); }
            res = StVal(res, segT.query(posInBase[chainHead[chainV]], posInBase[v]));
        }
        if (depth[u] > depth[v]){ swap(u, v); }
        // u is the LCA of the initial (u,v)
        return StVal(res, segT.query(posInBase[u], posInBase[v]));
        // return StVal(res, segT.query(posInBase[u] + 1, posInBase[v])); // For edge values
    }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q;
	tree t(n);
	for (int i = 0; i < n; i++) {
		cin >> t.nodes[i].val;
	}
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

    t.initializeHLD();

    while (q--) {
		int op; cin >> op;
		if (op == 1) {
			int s; ll x; cin >> s >> x; s--;
            t.updateVal(s, x);
		}
		else {
			int v; cin >> v; v--;
			cout << t.query(0, v) << '\n';
		}
	}
}