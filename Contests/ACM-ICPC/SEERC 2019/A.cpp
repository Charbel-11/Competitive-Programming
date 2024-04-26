#include <bits/stdc++.h>
using namespace std;

struct StVal {
    int S = 0, lVal = 0, rVal = 0;
    int len = 0, prefAlt = 0, sufAlt = 0;
    StVal() {}
    StVal(const int _v) : lVal(_v), rVal(_v) {
        len = prefAlt = sufAlt = 1;
    }
    StVal(const StVal &v1, const StVal &v2) {
        len = v1.len + v2.len;
        S = v1.S + v2.S;
        prefAlt = v1.prefAlt;
        sufAlt = v2.sufAlt;
        if (v1.rVal != v2.lVal && v1.rVal != 0 && v2.rVal != 0){
            S = S - (v1.sufAlt/2) - (v2.prefAlt/2) + (v1.sufAlt + v2.prefAlt)/2;
            prefAlt += (v1.prefAlt == v1.len ? v2.prefAlt : 0);
            sufAlt += (v2.sufAlt == v2.len ? v1.sufAlt : 0);
        }
        lVal = v1.lVal;
        rVal = v2.rVal;
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
            st[si] = StVal(1);			//Set the actual array here
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

	int n, m; cin >> n >> m;
    vector<vector<int>> indices(m + 1, vector<int>());
    for(int i = 0; i < n; i++){
        int cur; cin >> cur;
        indices[cur].push_back(i);
    }

    SegTree st(n);
    vector<int> ans(m + 1, -1);
    for(int i = 1; i <= m; i++){
        if (indices[i].empty()){ continue; }
        for(auto &idx : indices[i]){ st.update(idx, 0); }

        int curAns = 0;
        int curS = indices[i].size();
        for(int j = 0; j < curS; j++){
            int curIdx = indices[i][j];
            int nxtIdx = indices[i][(j+1) % curS];

            int curVal = 0;
            if (nxtIdx > curIdx){
                StVal curQ = st.query(curIdx + 1, nxtIdx - 1);
                curVal = curQ.S;
            }
            else{
                StVal rInt = st.query(curIdx + 1, n - 1);
                StVal lInt = st.query(0, nxtIdx - 1);
                StVal joined = StVal(rInt, lInt);
                curVal = joined.S;
            }
            curAns += curVal;
        }

        curAns += n - indices[i].size();
        ans[i] = curAns;

        for(auto &idx : indices[i]){ st.update(idx, -1); }
    }

    for(int i = 1; i <= m; i++){
        cout << ans[i] << ' ';
    }
}