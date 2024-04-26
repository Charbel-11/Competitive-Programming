#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct StVal {
    ll v = -1; StVal() {}
    StVal(const ll _v) : v(_v) {}
    StVal(const StVal &v1, const StVal &v2) { v = max(v1, v2); }
    operator ll() const { return v; }
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
        st[si] = StVal(c);
        for (si >>= 1; si; si >>= 1)
            st[si] = StVal(st[si << 1], st[si << 1 | 1]);
    }
};

bool comp(const array<int, 3>& a, const array<int, 3>& b){
    if (a[1] != b[1]){ return a[1] > b[1]; }
    return a[0] < b[0];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n; cin >> n;
    vector<int> ans(n, 0);

    vector<array<int, 3>> intervals;
    vector<int> comp;
    for(int i = 0; i < n; i++){
        int a, t; cin >> a >> t;
        int b = a + t;
        comp.push_back(a);
        comp.push_back(b);
        intervals.push_back({a, b, i});
    }
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    SegTree st(comp.size() + 1);

    for(int i = 0; i < n; i++){
        intervals[i][0] = lower_bound(comp.begin(), comp.end(), intervals[i][0]) - comp.begin();
        intervals[i][1] = lower_bound(comp.begin(), comp.end(), intervals[i][1]) - comp.begin();
    }
    sort(intervals.begin(), intervals.end(), [](const array<int, 3>& a, const array<int, 3>& b)
    {
        if (a[1] != b[1]){ return a[1] > b[1]; }
        return a[0] < b[0];
    });

    for(int i = 0; i < n; i++){
        ans[intervals[i][2]] = 1 + st.query(0, intervals[i][0]);
        st.update(intervals[i][0], ans[intervals[i][2]]);
    }

    for(auto &x : ans){ cout << x << ' '; }
    cout << '\n';
}