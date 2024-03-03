#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct StVal {
    double v = 0; StVal() {}
    StVal(const double _v) : v(_v) {}
    StVal(const StVal &v1, const StVal &v2) { v = min(v1.v, v2.v); }
};

struct StUpdate {
    double v = 0; StUpdate() {}
    StUpdate(const double v) : v(v) {}
    StUpdate(const StUpdate &u1, const StUpdate &u2) { v = u1.v + u2.v; }	//Combine two lazy values, u2 is always the parent (which can have priority)
    void apply(StVal &sv, const int lo, const int hi) {	//Changes the current answer (Stval not Stupdate) according to the lazy value
        sv.v += this->v;				//Could be called even if v=0
    }
};

struct SegTree {
    int n;
    vector<StVal> st;
    vector<StUpdate> lazy;
    vector<int> leaves;

    SegTree(const int n) : n(n) {
        leaves.resize(n);
        init(1, 0, n - 1);
        lazy.resize(st.size());
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

double dist(ll x1, ll y1, ll x2, ll y2){
    ll dx = x1 - x2, dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, k; cin >> n >> k;
    ll sx, sy; cin >> sx >> sy;

    vector<pair<ll, ll>> pts(n);
    for(auto &p : pts){ cin >> p.first >> p.second; }

    SegTree st(n);
    vector<double> dp(n, -1);
    for(int i = 0; i < n; i++){
        auto [x, y] = pts[i];
        double curDist = dist(sx, sy, x, y);

        if (i > 0){
            double curDiff = dist(x, y, pts[i-1].first, pts[i-1].second);
            st.update(0, i-1, curDiff);
        }

        int l = max(i - k + 1, 0);
        st.update(i, i, (i > 0 ? dp[i-1] : 0.0) + curDist);
        dp[i] = curDist + st.query(l, i).v;
    }

    cout << setprecision(8) << fixed << dp[n - 1] << '\n';
}

