#include <bits/stdc++.h>
using namespace std;

vector<int> base;

struct StVal {
    int m1 = 0, f1 = 0, m2 = 0, f2 = 0; StVal() {}
    StVal(const int _v) : m1(_v), f1(1) {}
    StVal(const StVal &v1, const StVal &v2) {
        int newM1 = max(v1.m1, v2.m1);
        int newM2 = max(v1.m2, v2.m2);
        if (v1.m1 != newM1){ newM2 = max(newM2, v1.m1); }
        if (v2.m1 != newM1){ newM2 = max(newM2, v2.m1); }

        int newF1 = 0, newF2 = 0;
        if (v1.m1 == newM1){ newF1 += v1.f1; }
        if (v2.m1 == newM1){ newF1 += v2.f1; }

        if (v1.m1 == newM2){ newF2 += v1.f1; }
        if (v2.m1 == newM2){ newF2 += v2.f1; }
        if (v1.m2 == newM2){ newF2 += v1.f2; }
        if (v2.m2 == newM2){ newF2 += v2.f2; }

        m1 = newM1; m2 = newM2;
        f1 = newF1; f2 = newF2;
    }
};

struct SegTree {
    int n;
    vector<int> leaves;
    vector<StVal> st;	//st[1] root; To go to a child, *2 (l) or *2+1 (r);	To go to a parent: /2

    SegTree(const int n) : n(n) {
        leaves.resize(n);
        init(1, 0, n - 1);
    }

    //lo, hi indices of the actual array; si is the index of the segment tree array
    void init(const int si, const int lo, const int hi) {
        if (lo == hi) {
            if (si >= (int)st.size()) { st.resize(si + 1); }
            st[si] = StVal(base[lo]);			//Set the actual array here
            leaves[lo] = si;
            return;
        }
        int lC = si << 1, rC = (si << 1) | 1, mid = (lo + hi) >> 1;
        init(lC, lo, mid); init(rC, mid + 1, hi);
        st[si] = StVal(st[lC], st[rC]);
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

    //Change a leaf and update its ancestors' values
    void update(const int i, int c) {
        int si = leaves[i];
        st[si] = StVal(c);
        for (si >>= 1; si; si >>= 1)
            st[si] = StVal(st[si << 1], st[si << 1 | 1]);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, q; cin >> n >> q;
    base.resize(n); for(auto &x : base){ cin >> x; }
    SegTree st(n);

    while(q--){
        int type; cin >> type;
        if (type == 1){
            int p, x; cin >> p >> x; p--;
            st.update(p, x);
        }
        else{
            int l, r; cin >> l >> r; l--; r--;
            auto ans = st.query(l, r);
            cout << ans.f2 << '\n';
        }
    }
}

