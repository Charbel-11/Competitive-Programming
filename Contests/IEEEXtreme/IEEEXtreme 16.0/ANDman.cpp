#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

vector <ll> W, base;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
    ll res = 1;
    for (; p; p >>= 1, x = (x * x) % mod) {
        if (p & 1) { res = (res * x) % mod; }
    }
    return res;
}
// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

struct StVal {
	ll v = 1; StVal() {}
	StVal(const ll _v) : v(_v) {}
	StVal(const StVal &v1, const StVal &v2) { v = (v1 * v2) % mod; }
	operator ll() const { return v; }
};

struct StUpdate {
	ll v = 1; StUpdate() {}
	StUpdate(const ll v) : v(v) {}
	StUpdate(const StUpdate &u1, const StUpdate &u2) { v = (u1 * u2) % mod; }
	operator ll() const { return v; }
	void apply(StVal &sv, const int lo, const int hi) {
		sv.v = (this->v * sv.v) % mod;
	}
};

struct SegTree {
	int n;
	vector<StVal> st;
	vector<StUpdate> lazy;

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
		} else {
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

struct node { vector<edge> edges; };

vector<int> start, finish;
struct tree {
    vector<vector<int>> anc;
    vector<node> nodes;
    vector<int> depth;

    int root, n, lg2;

    tree(int _n, int _r = 0) : n(_n), root(_r) {
        lg2 = (int)(ceil(log2(n + 1.0)));
        nodes.resize(n); depth.resize(n, 0);
        anc.resize(n + 1, vector<int>(lg2 + 1, -1));
        start.resize(n, -1); finish.resize(n, -1);
    }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

    void preprocess() {
        queue<int> q; q.push(root);
        vector<bool> visited(n, false);
        visited[root] = true;
        anc[root][0] = root;

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            for (auto &e : nodes[cur].edges) {
                if (visited[e.v]) { continue; }
                anc[e.v][0] = cur;
                depth[e.v] = depth[cur] + 1;
                q.push(e.v); visited[e.v] = true;
            }
        }
        for (int i = 1; i <= lg2; i++)
            for (int u = 0; u < n; u++)
                anc[u][i] = anc[anc[u][i - 1]][i - 1];
    }

    int LCA(int u, int v) {
        if (depth[u] < depth[v]) { swap(u, v); }

        for (int i = lg2; i >= 0; i--) {
            if (depth[u] - (1 << i) >= depth[v])
                u = anc[u][i];	//furthest parent found is 2^i
        }

        if (u == v) { return v; }

        for (int i = lg2; i >= 0; i--) {
            if (anc[u][i] != anc[v][i]) {
                u = anc[u][i];
                v = anc[v][i];
            }
        }

        return anc[u][0];
    }

	void preorder(int u, int &t) {
		start[u] = t; t++;
		for (auto &x : nodes[u].edges) {
			if (start[x.v] == -1) { preorder(x.v, t); }
		}
		finish[u] = t - 1;
	}

    void fillBase(int u, int p, ll cur = 1){
        cur = (cur * W[u]) % mod;
        base[start[u]] = cur;
        for(auto &e : nodes[u].edges){
            if (e.v == p){ continue; }
            fillBase(e.v, u, cur);
        }
    }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    int t; cin >> t;
    while(t--){
        start.clear(); finish.clear();
        int n; cin >> n;
        tree g(n);
        W.clear(); W.resize(n);
        base.clear(); base.resize(n, 1);
        for(auto &x : W){ cin >> x; }
        for(int i = 0; i < n-1; i++){
            int u,v; cin >> u >> v; u--; v--;
            g.add_edge(u, v);
        }

        int cnt = 0;
        g.preprocess();
        g.preorder(0, cnt);
        g.fillBase(0, -1, 1);
        SegTree st(n);

        int q; cin >> q;
        while(q--){
            int type; cin >> type;
            if (type == 1){
                int u; ll v; cin >> u >> v; u--;
                ll factor = (modinv(W[u]) * v) % mod;
                W[u] = v;
                st.update(start[u], finish[u], StUpdate(factor));
            }
            else{
                int u, v; cin >> u >> v; u--; v--;
                int lca = g.LCA(u, v);
                ll qU = st.query(start[u], start[u]), qV = st.query(start[v], start[v]);
                ll ans = (qU * qV) % mod;
                ll lcaPathVal = modinv(st.query(start[lca], start[lca]));
                ans *= lcaPathVal; ans %= mod;
                ans *= lcaPathVal; ans %= mod;
                ans *= W[lca]; ans %= mod;

                cout << ans << '\n';
            }
        }
    }
}