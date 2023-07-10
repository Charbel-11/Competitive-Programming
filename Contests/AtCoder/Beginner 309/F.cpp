#include <bits/stdc++.h>
using namespace std;

struct StVal {
    int v = 1e9+5; StVal() {}
    StVal(const int _v) : v(_v) {}
    StVal(const StVal &v1, const StVal &v2) { v = min(v1, v2); }
    operator int() const { return v; }	//Casts StVal to int
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
            st[si] = StVal();			//Set the actual array here
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
        if (st[si].v < c){ return; }
        st[si] = StVal(c);
        for (si >>= 1; si; si >>= 1)
            st[si] = StVal(st[si << 1], st[si << 1 | 1]);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int N; cin >> N;
    vector<array<int, 3>> vals(N);
    vector<int> comp;
    for(int i = 0; i < N; i++){
        int h, w, d; cin >> h >> w >> d;
        vals[i] = {h, w, d};
        sort(vals[i].begin(), vals[i].end());
        for(auto &x : vals[i]) { comp.push_back(x); }
    }

    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    for(auto &v : vals){
        for(auto &x: v){
            x = lower_bound(comp.begin(), comp.end(), x) - comp.begin();
        }
    }

    bool OK = false;
    SegTree st(comp.size() + 1);
    vector<array<int, 3>> buffer;
    sort(vals.begin(), vals.end());
    for(int i = 0; i < N; i++){
        if (i && vals[i][0] > vals[i-1][0]){
            for(auto &v : buffer){
                st.update(v[1], v[2]);
            }
            buffer.clear();
        }

        if (st.query(0, vals[i][1] - 1) < vals[i][2]) {
            OK = true;
            break;
        }
        buffer.push_back(vals[i]);
    }

    cout << (OK ? "Yes" : "No") << '\n';
}