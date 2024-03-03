#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
vector<ll> base;

struct StVal {
    int minIdx = -1, maxIdx = -1;
    ll vMax = 0, vMin = 1e9+6; StVal() {}
    StVal(const ll _v, const int _idx) : vMax(_v), vMin(_v), minIdx(_idx), maxIdx(_idx) {}
    StVal(const StVal &v1, const StVal &v2) {
        if (v1.vMax > v2.vMax){
            vMax = v1.vMax;
            maxIdx = v1.maxIdx;
        }
        else if (v1.vMax == v2.vMax){
            vMax = v1.vMax;
            maxIdx = min(v1.maxIdx, v2.maxIdx);
        }
        else{
            vMax = v2.vMax;
            maxIdx = v2.maxIdx;
        }

        if (v1.vMin < v2.vMin){
            vMin = v1.vMin;
            minIdx = v1.minIdx;
        }
        else if (v1.vMin == v2.vMin){
            vMin = v1.vMin;
            minIdx = min(v1.minIdx, v2.minIdx);
        }
        else{
            vMin = v2.vMin;
            minIdx = v2.minIdx;
        }
    }
};

struct StUpdate {
    bool flip = false; StUpdate() {}
    StUpdate(const bool f) : flip(f) {}
    StUpdate(const StUpdate &u1, const StUpdate &u2) { flip = u1.flip ^ u2.flip; }
    void apply(StVal &sv, const int lo, const int hi) {	//Changes the current answer (Stval not Stupdate) according to the lazy value
        if (flip){
            ll oldMin = sv.vMin, oldMax = sv.vMax;
            sv.vMin = mod - oldMax;
            sv.vMax = mod - oldMin;
            swap(sv.minIdx, sv.maxIdx);
        }
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
            st[si] = StVal(base[lo], lo);			//Set the actual array here
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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ifstream cin("in.txt");
    ofstream cout("out.txt");

    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        int n; cin >> n;
        base.clear(); base.resize(n);
        for(auto &x : base){ cin >> x; }

        SegTree st(n);
        ll ans = 0; int q; cin >> q;
        while(q--){
            int l, r; cin >> l >> r; l--; r--;
            st.update(l, r, StUpdate(true));
            auto curAns = st.query(0, n-1);
            ans += curAns.maxIdx + 1;
        }

        cout << "Case #" << qq << ": " << ans << '\n';
    }
}