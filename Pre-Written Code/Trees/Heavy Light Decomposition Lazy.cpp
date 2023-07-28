//Handles path updates and path queries in O(log^2n)
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

struct StUpdate {
	ll v = 0; StUpdate() {}
	StUpdate(const ll v) : v(v) {}
	StUpdate(const StUpdate &u1, const StUpdate &u2) { v = u1 + u2; }	//Combine two lazy values (we must change v in all cases otherwise it will reset)
	operator ll() const { return v; }
	void apply(StVal &sv, const int lo, const int hi) {	//Changes the current answer (Stval not Stupdate) according to the lazy value
		sv.v += (ll)(hi - lo + 1)*v;
	}
};

struct SegTree {
	int n;
	vector<StVal> st;
	vector<StUpdate> lazy;

    SegTree() {}
	SegTree(const int n) : n(n) {
		init(1, 0, n - 1);
		lazy.resize(st.size());
	}

	//lo, hi indices of the actual array; si is the index of the segment tree array
	void init(const int si, const int lo, const int hi) {
		if (lo == hi) {
			if (si >= (int)st.size()) { st.resize(si + 1); }
			st[si] = StVal(base[lo]);			//Set the actual array here
			return;
		}
		int lC = si << 1, rC = (si << 1) | 1, mid = (lo + hi) >> 1;
		init(lC, lo, mid); init(rC, mid + 1, hi);
		st[si] = StVal(st[lC], st[rC]);
	}

	void updateLazy(const int si, const int lo, const int hi) {
		lazy[si].apply(st[si], lo, hi);
		if (lo != hi) {
			lazy[si << 1] = StUpdate(lazy[si << 1], lazy[si]);
			lazy[si << 1 | 1] = StUpdate(lazy[si << 1 | 1], lazy[si]);
		}
		lazy[si] = StUpdate();
	}

	StVal query(const int l, const int r) { return (l <= r && l < n && r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
	StVal query(const int l, const int r, const int si, const int lo, const int hi) {
		updateLazy(si, lo, hi);
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
	}

	void update(const int l, const int r, const StUpdate& u) { if (l <= r) update(l, r, u, 1, 0, n - 1); }
	void update(const int l, const int r, const StUpdate &u, const int si, const int lo, const int hi) {
		if (l <= lo && hi <= r) {
			lazy[si] = StUpdate(lazy[si], u);
			updateLazy(si, lo, hi);
		}
		else {
			updateLazy(si, lo, hi);
			if (hi < l || r < lo) return;
			const int mid = (lo + hi) >> 1;
			update(l, r, u, si << 1, lo, mid);
			update(l, r, u, si << 1 | 1, mid + 1, hi);
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
		}
	}
};

struct edge {
	int u, v, w; edge() {}
	edge(int _u, int _v, int _w) :
		u(_u), v(_v), w(_w) {}
};
struct node { vector<int> edges; };

struct tree {
    SegTree segT;
    vector<int> parent;
    vector<edge> edges;	vector<node> nodes;
    vector<int> depth, subtreeSize;
    vector<int> chainHead, chainIdx, posInBase;
//	vector<int> chainSize, chainPos;
    int root, n, chainNum, ptr;

    tree(int _n, int _r = 0) : n(_n), root(_r) {
        nodes.resize(n); parent.resize(n, -1);
        depth.resize(n, 0); subtreeSize.resize(n, 1);
        chainNum = 0; ptr = 0; posInBase.resize(n);
        chainHead.resize(n, -1); chainIdx.resize(n);
        //	chainPos.resize(n); chainSize.resize(n);
    }

    void add_edge(int u, int v, int w) {
        edge e1(u, v, w); edge e2(v, u, w);
        nodes[u].edges.push_back(edges.size()); edges.push_back(e1);
        nodes[v].edges.push_back(edges.size()); edges.push_back(e2);
    }

    void initializeHLD(){
        base.clear(); base.resize(n);
        dfsPre(0, -1);
        hld(0, -1, -1);     //here we are setting edge values
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

    void hld(int cur, int p, int cost) {
        if (chainHead[chainNum] == -1) { chainHead[chainNum] = cur; }
        chainIdx[cur] = chainNum;
        //	chainPos[cur] = chainSize[chainNum];
        //	chainSize[chainNum]++;

        posInBase[cur] = ptr;	//sets the idx of the node in the segment tree array
        base[ptr++] = cost;		//sets the actual array

        int idx = -1, maxS = -1, nCost = -1;
        for (auto &eIdx : nodes[cur].edges) {
            auto &e = edges[eIdx];
            if (e.v == p) { continue; }
            if (subtreeSize[e.v] > maxS) {
                maxS = subtreeSize[e.v];
                idx = e.v; nCost = e.w;
            }
        }

        if (idx >= 0) { hld(idx, cur, nCost); }
        for (auto &eIdx : nodes[cur].edges) {
            auto &e = edges[eIdx];
            if (e.v == p || e.v == idx) { continue; }
            chainNum++; hld(e.v, cur, e.w);
        }
    }

    //O(log^2n)
    void pathUpdate(int u, int v, const StUpdate& U) {
        int chainU = chainIdx[u], chainV = chainIdx[v];
        for(; chainU != chainV; v = parent[chainHead[chainV]], chainV = chainIdx[v]){
            if (depth[chainHead[chainU]] > depth[chainHead[chainV]]) { swap(u, v); swap(chainU, chainV); }
            segT.update(posInBase[chainHead[chainV]], posInBase[v], U);
        }
        if (depth[u] > depth[v]){ swap(u, v); }
      //  segT.update(posInBase[u], posInBase[v], U);       // For node values
        segT.update(posInBase[u] + 1, posInBase[v], U);       // For edge values
    }

    //O(log^2n)
    StVal pathQuery(int u, int v) {
        StVal res = StVal();
        int chainU = chainIdx[u], chainV = chainIdx[v];
        for(; chainU != chainV; v = parent[chainHead[chainV]], chainV = chainIdx[v]){
            if (depth[chainHead[chainU]] > depth[chainHead[chainV]]) { swap(u, v); swap(chainU, chainV); }
            res = StVal(segT.query(posInBase[chainHead[chainV]], posInBase[v]), res);
        }
        if (depth[u] > depth[v]){ swap(u, v); }
        // u is the LCA of the initial (u,v)
        //   return StVal(segT.query(posInBase[u], posInBase[v]), res);  // For node values
        return StVal(segT.query(posInBase[u] + 1, posInBase[v]), res); // For edge values
    }

    //POINT UPDATES (requires point update in seg tree)
    /*
       //For node values
    void updateVal(int u, int newVal) {
        segT.update(posInBase[u], newVal);
    }

    //For edge values, we update the node which has that edge as parent
    void updateEdgeVal(int eN, int newVal) {
        int u1 = edges[eN * 2].u, v1 = edges[eN * 2].v;
        int lower = (depth[u1] > depth[v1] ? u1 : v1);
        segT.update(posInBase[lower], newVal);
    }
    */
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v, w; cin >> u >> v >> w; u--; v--;
		t.add_edge(u, v, w);
	}

	t.initializeHLD();

	while (m--) {
		char op; cin >> op;
		if (op == 'P') {
			int u, v; cin >> u >> v; u--; v--;
			t.pathUpdate(u, v, StUpdate(1));
		}
		else {
			int u, v; cin >> u >> v; u--; v--;
			cout << t.pathQuery(u, v) << '\n';
		}
	}
}