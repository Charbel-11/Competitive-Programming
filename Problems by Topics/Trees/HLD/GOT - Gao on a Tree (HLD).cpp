//https://www.spoj.com/problems/GOT/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct StVal {
    int v = -1; StVal() {}
    StVal(const int _v) : v(_v) {}
    StVal(const StVal& v1, const StVal& v2) { v = max(v1, v2); }
    operator int() const { return v; }
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

    //lo, hi indices of the actual array; si is the index of the segment tree array
    void init(const int si, const int lo, const int hi) {
        if (lo == hi) {
            if (si >= (int)st.size()) { st.resize(si + 1); }
            st[si] = StVal();			//Set the actual array here
            leaves[lo] = si;
            return;
        }
        int lC = si << 1, rC = (si << 1) | 1, mid = (lo + hi) >> 1;
        init(lC, lo, mid); init(rC, mid + 1, hi);
        st[si] = StVal(st[lC], st[rC]);
    }

    //l and r inclusive, 0-indexed
    StVal query(const int l, const int r) { return (l <= r && l < n&& r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
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
    int u, v; edge() {}
    edge(int _u, int _v) :
            u(_u), v(_v) {}
};
struct node { vector<int> edges; };

struct tree {
    SegTree segT;
    vector<int> parent;
    vector<edge> edges;	vector<node> nodes;
    vector<int> depth, subtreeSize;
    vector<int> chainHead, chainIdx, posInBase;
    int root, n, chainNum, ptr;

    tree(int _n, int _r = 0) : n(_n), root(_r) {
        nodes.resize(n); parent.resize(n, -1);
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
        posInBase[cur] = ptr++;	//sets the idx of the node in the segment tree array

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
    void updateVal(int u, int newVal) {
        segT.update(posInBase[u], newVal);
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
        return StVal(segT.query(posInBase[u], posInBase[v]), res);  // For node values
    }
};

struct query {
    bool set;
    int u, v, c, idx;

    query(bool _b, int _u, int _v, int _c, int _id = -1) :u(_u), v(_v), c(_c), set(_b), idx(_id) {}

    bool operator<(query& rhs) {
        if (rhs.c == c) { return set; }
        return c < rhs.c;
    }
};

static bool comp(query& lhs, query& rhs) {
    if (lhs.c == rhs.c) { return lhs.set; }
    return lhs.c < rhs.c;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    while(true){
        int n, m; cin >> n;
        if (cin.fail()) { break; }
        cin >> m; tree t(n);
        vector<query> queries;
        for (int i = 0; i < n; i++) {
            int c; cin >> c;
            queries.emplace_back(true, i, i, c);
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v; cin >> u >> v; u--; v--;
            t.add_edge(u, v);
        }

        for(int i = 0; i < m; i++){
            int u, v, c; cin >> u >> v >> c; u--; v--;
            queries.emplace_back(false, u, v, c, i);
        }
        sort(queries.begin(), queries.end(), comp);

        t.initializeHLD();

        vector<bool> ans(m);
        for (auto& q : queries) {
            if (q.set) { t.updateVal(q.u, q.c); }
            else { ans[q.idx] = (t.pathQuery(q.u, q.v) == q.c); }
        }

        for (bool x : ans) { cout << (x ? "Find" : "NotFind") << '\n'; }
        cout << endl;
    }
}