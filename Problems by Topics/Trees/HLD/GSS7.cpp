//https://www.spoj.com/problems/GSS7/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> base;

struct StVal {
    ll maxPref = 0, maxSuf = 0, maxAns = 0, sum = 0; StVal() {}
    StVal(const ll _v) { maxPref = maxSuf = maxAns = max(0ll, _v); sum = _v; }
    StVal(const StVal &v1, const StVal &v2) {
        sum = v1.sum + v2.sum;
        maxPref = max(v1.maxPref, v1.sum + v2.maxPref);
        maxSuf = max(v2.maxSuf, v2.sum + v1.maxSuf);
        maxAns = max(v1.maxAns, v2.maxAns);
        maxAns = max(maxAns, v1.maxSuf + v2.maxPref);
    }
    operator ll() const { return maxAns; }
};

struct StUpdate {
    ll v = 0; bool b = 0; StUpdate() {}
    StUpdate(const ll v, const bool b) : v(v), b(b) {}
    StUpdate(const StUpdate &u1, const StUpdate &u2) {
        if (u2.b) { v = u2.v; b = 1; }
        else { v = u1.v; b = u1.b; }
    }
    operator ll() const { return v; }
    void apply(StVal &sv, const int lo, const int hi) {	//Changes the current answer (Stval not Stupdate) according to the lazy value
        if (b) {
            sv.sum = (ll)(hi - lo + 1)*v;
            sv.maxPref = sv.maxSuf = sv.maxAns = max(sv.sum, 0ll);
        }
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

    void update(const int l, const int r, const StUpdate u) { if (l <= r) update(l, r, u, 1, 0, n - 1); }
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
//	vector<int> chainSize, chainPos;
    int root, n, chainNum, ptr;

    tree(int _n, int _r = 0) : n(_n), root(_r) {
        nodes.resize(n); parent.resize(n, -1);
        depth.resize(n, 0); subtreeSize.resize(n, 1);
        chainNum = 0; ptr = 0; posInBase.resize(n);
        chainHead.resize(n, -1); chainIdx.resize(n);
        //	chainPos.resize(n); chainSize.resize(n);
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
        //	chainPos[cur] = chainSize[chainNum];
        //	chainSize[chainNum]++;

        posInBase[cur] = ptr;	//sets the idx of the node in the segment tree array
        base[ptr++] = nodes[cur].val;		//sets the actual array

        int idx = -1, maxS = -1, nCost = -1;
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

    //O(log^2n)
    void pathUpdate(int u, int v, const StUpdate& U) {
        int chainU = chainIdx[u], chainV = chainIdx[v];
        for(; chainU != chainV; v = parent[chainHead[chainV]], chainV = chainIdx[v]){
            if (depth[chainHead[chainU]] > depth[chainHead[chainV]]) { swap(u, v); swap(chainU, chainV); }
            segT.update(posInBase[chainHead[chainV]], posInBase[v], U);
        }
        if (depth[u] > depth[v]){ swap(u, v); }
        segT.update(posInBase[u], posInBase[v], U);       // For node values
    }

    //O(log^2n)
    StVal pathQuery(int u, int v) {
        StVal pathU = StVal(), pathV = StVal();
        int chainU = chainIdx[u], chainV = chainIdx[v];
        for(; chainU != chainV; v = parent[chainHead[chainV]], chainV = chainIdx[v]){
            if (depth[chainHead[chainU]] > depth[chainHead[chainV]]) {
                swap(u, v); swap(chainU, chainV);
                swap(pathU, pathV);
            }
            pathV = StVal(segT.query(posInBase[chainHead[chainV]], posInBase[v]), pathV);
        }
        if (depth[u] > depth[v]){ swap(u, v); swap(pathU, pathV); }
        pathV = StVal(segT.query(posInBase[u], posInBase[v]), pathV);
        swap(pathU.maxPref, pathU.maxSuf);
        return StVal(pathU, pathV);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n; cin >> n;
    tree t(n);
    for (int i = 0; i < n; i++) { cin >> t.nodes[i].val; }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        t.add_edge(u, v);
    }
    t.initializeHLD();

    int Q; cin >> Q;
    while (Q--) {
        int op; cin >> op;
        if (op == 2) {
            int u, v; ll val; cin >> u >> v >> val; u--; v--;
            t.pathUpdate(u, v, StUpdate(val, true));
        }
        else {
            int u, v; cin >> u >> v; u--; v--;
            cout << t.pathQuery(u, v) << '\n';
        }
    }
}