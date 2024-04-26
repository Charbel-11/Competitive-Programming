#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> base;

struct StVal {
    ll mxHeights = 0, sumMins = 0; StVal() {}
    StVal(const ll _h) : mxHeights(_h) {}
    StVal(const StVal &v1, const StVal &v2) {
        mxHeights = max(v1.mxHeights, v2.mxHeights);
        sumMins = v1.sumMins + v2.sumMins;
    }
};

struct StUpdate {
    ll heightAdd = 0, sumMinSet = -1; StUpdate() {}
    StUpdate(const ll hA, const ll minSet = -1) : heightAdd(hA), sumMinSet(minSet) {}
    StUpdate(const StUpdate &u1, const StUpdate &u2) {
        if (u2.sumMinSet != -1){
            sumMinSet = u2.sumMinSet;
        }
        else{ sumMinSet = u1.sumMinSet; }
        heightAdd = u1.heightAdd + u2.heightAdd;
    }
    void apply(StVal &sv, const int lo, const int hi) {	//Changes the current answer (Stval not Stupdate) according to the lazy value
        sv.mxHeights += heightAdd;
        if (sumMinSet != -1) {
            sv.sumMins = sumMinSet * (hi-lo+1);
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
            st[si] = StVal(base[lo]);			//Set the actual array here
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

    //l and r inclusive, 0-indexed
    int leftMostLarger(const int l, const int r, const ll val) { return (l <= r && l < n && r >= 0) ? leftMostLarger(val, l, r, 1, 0, n - 1) : -1; }
    int leftMostLarger(const ll val, const int l, const int r, const int si, const int lo, const int hi) {
        updateLazy(si, lo, hi);
        const int mid = (lo + hi) >> 1;
        if (l <= lo && hi <= r) {
            if (st[si].mxHeights < val){ return -1; }
            if (lo == hi){ return lo; }
            int lC = si << 1, rC = si << 1 | 1;
            updateLazy(lC, lo, mid);  updateLazy(rC, mid+1, hi);
            if (st[lC].mxHeights >= val){ return leftMostLarger(val, l, r, lC, lo, mid); }
            else { return leftMostLarger(val, l, r, rC, mid+1, hi); }
        }

        if (r <= mid) return leftMostLarger(val, l, r, si << 1, lo, mid);
        if (mid < l) return leftMostLarger(val, l, r, si << 1 | 1, mid + 1, hi);

        int res1 = leftMostLarger(val, l, r, si << 1, lo, mid);
        if (res1 != -1){ return res1; }
        return leftMostLarger(val, l, r, si << 1 | 1, mid + 1, hi);
    }

    int rightMostLarger(const int l, const int r, const ll val) { return (l <= r && l < n && r >= 0) ? rightMostLarger(val, l, r, 1, 0, n - 1) : -1; }
    int rightMostLarger(const ll val, const int l, const int r, const int si, const int lo, const int hi) {
        updateLazy(si, lo, hi);
        const int mid = (lo + hi) >> 1;
        if (l <= lo && hi <= r) {
            if (st[si].mxHeights < val){ return -1; }
            if (lo == hi){ return lo; }
            int lC = si << 1, rC = si << 1 | 1;
            updateLazy(lC, lo, mid);  updateLazy(rC, mid+1, hi);
            if (st[rC].mxHeights >= val) { return rightMostLarger(val, l, r, rC, mid+1, hi); }
            else{ return rightMostLarger(val, l, r, lC, lo, mid); }
        }

        if (r <= mid) return rightMostLarger(val, l, r, si << 1, lo, mid);
        if (mid < l) return rightMostLarger(val, l, r, si << 1 | 1, mid + 1, hi);

        int res1 = rightMostLarger(val, l, r, si << 1 | 1, mid + 1, hi);
        if (res1 != -1){ return res1; }
        return  rightMostLarger(val, l, r, si << 1, lo, mid);
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

	int t; cin >> t;
	while(t--){
		int n; cin >> n; ll curAns = 0;
        base.clear(); base.resize(n);
        for(auto& x : base){ cin >> x; curAns -= x; }

        SegTree st(n);
        for(int i = 0; i < n; i++){
            ll max1 = st.query(0, i).mxHeights;
            ll max2 = st.query(i, n-1).mxHeights;
            ll curMin = min(max1, max2); curAns += curMin;
            st.update(i, i, StUpdate(0, curMin));
        }

        int q; cin >> q;
        while(q--){
            int x; ll v; cin >> x >> v; x--;
            curAns -= v; base[x] += v;
            ll newHeight = base[x];

            int beforeLarger = st.rightMostLarger(0, x-1, newHeight);
            int afterLarger = st.leftMostLarger(x+1, n-1, newHeight);
            if (beforeLarger == -1 && afterLarger == -1){
                ll oldMin = st.query(x, x).sumMins;
                curAns += newHeight - oldMin;
                st.update(x, x, StUpdate(0, newHeight));
            }
            else if (beforeLarger == -1 || afterLarger == -1){
                int firstAffected = x, lastAffected = afterLarger - 1;
                if (afterLarger == -1){
                    firstAffected = beforeLarger + 1, lastAffected = x;
                }

                ll numAffected = lastAffected - firstAffected + 1;
                ll prevSum = st.query(firstAffected, lastAffected).sumMins;
                curAns += newHeight * numAffected - prevSum;
                st.update(firstAffected, lastAffected, StUpdate(0, newHeight));
            }

            cout << curAns << '\n';
            st.update(x, x, StUpdate(v));
        }
	}
}

