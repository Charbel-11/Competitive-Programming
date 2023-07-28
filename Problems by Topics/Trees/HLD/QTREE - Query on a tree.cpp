//https://www.spoj.com/problems/QTREE/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> base;

struct StVal {
    int v = 0; StVal() {}
    StVal(const int _v) : v(_v) {}
    StVal(const StVal &v1, const StVal &v2) { v = max(v1, v2); }
    operator int() const { return v; }
};
struct SegTree {
    int n;
    vector<StVal> st;
    vector<int> leaves;

    SegTree(){}
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
    void update(const int i, int c) {
        int si = leaves[i];
        st[si] = StVal(c);
        for (si >>= 1; si; si >>= 1)
            st[si] = StVal(st[si << 1], st[si << 1 | 1]);
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

    //For edge values, we update the node which has that edge as parent
    void updateEdgeVal(int eN, int newVal) {
        int u1 = edges[eN * 2].u, v1 = edges[eN * 2].v;
        int lower = (depth[u1] > depth[v1] ? u1 : v1);
        segT.update(posInBase[lower], newVal);
    }

    //O(log^2n)
    StVal pathQuery(int u, int v) {
        StVal res = StVal();
        int chainU = chainIdx[u], chainV = chainIdx[v];
        for(; chainU != chainV; v = parent[chainHead[chainV]], chainV = chainIdx[v]){
            if (depth[chainHead[chainU]] > depth[chainHead[chainV]]) { swap(u, v); swap(chainU, chainV); }
            res = StVal(res, segT.query(posInBase[chainHead[chainV]], posInBase[v]));
        }
        if (depth[u] > depth[v]){ swap(u, v); }
        // u is the LCA of the initial (u,v)
        //  return StVal(res, segT.query(posInBase[u], posInBase[v]));
        return StVal(res, segT.query(posInBase[u] + 1, posInBase[v])); // For edge values
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        tree t(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v, w; cin >> u >> v >> w; u--; v--;
            t.add_edge(u, v, w);
        }

        t.initializeHLD();

        string s; cin >> s;
        while (s[0] != 'D') {
            if (s[0] == 'C') {
                int eN, newVal; cin >> eN >> newVal; eN--;
                t.updateEdgeVal(eN, newVal);
            }
            else {
                int u, v; cin >> u >> v; u--; v--;
                cout << t.pathQuery(u, v) << '\n';
            }
            cin >> s;
        }
    }
}