#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll m1 = 8675309, m2 = 1e9 + 7;
vector<ll> base;

// fast exponentiation modulo mod
ll powe(ll x, ll p, ll mod) {
    ll res = 1;
    for (; p; p >>= 1, x = (x * x) % mod) {
        if (p & 1) { res = (res * x) % mod; }
    }
    return res;
}
// modular inverse (mod must be prime)
ll modinv(ll i, ll mod) { return powe(i, mod - 2, mod); }

struct StVal {
    ll s = 0, prod1 = 1, prod2 = 1, xx = 0; StVal() {}
    StVal(const ll _v) : s(_v), prod1(_v), prod2(_v), xx(_v) {}
    StVal(const StVal &v1, const StVal &v2) {
        s = v1.s + v2.s;
        prod1 = (v1.prod1 * v2.prod1) % m1;
        prod2 = (v1.prod2 * v2.prod2) % m2;
        xx = v1.xx ^ v2.xx;
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
    void update(const int i, ll c) {
        int si = leaves[i];
        st[si] = StVal(c);
        for (si >>= 1; si; si >>= 1)
            st[si] = StVal(st[si << 1], st[si << 1 | 1]);
    }
};

bool checkIfInRange(ll val, unordered_map<ll, set<int>>& numToIndices, int l, int r){
    auto& curSet = numToIndices[val];
    auto it = curSet.lower_bound(l);
    if (it != curSet.end() && *it <= r){ return true; }
    return false;
}
bool checkAlmostEqual(const StVal& val1, const StVal& val2, unordered_map<ll, set<int>>& numToIndices, int lBig, int rBig){
    ll diff = val1.s - val2.s;
    if (!checkIfInRange(diff, numToIndices, lBig, rBig)) { return false; }

    if (val2.prod1 != 0) {
        ll div1 = (val1.prod1 * modinv(val2.prod1, m1)) % m1;
        if (div1 != 0){
            if(!checkIfInRange(div1, numToIndices, lBig, rBig)){ return false; }
            if(diff != div1){ return false; }
        }
    }

    if (val2.prod2 != 0) {
        ll div2 = (val1.prod2 * modinv(val2.prod2, m2)) % m2;
        if (div2 != 0){
          if (!checkIfInRange(div2, numToIndices, lBig, rBig)){ return false; }
          if (diff != div2){ return false; }
        }
    }

    ll xorDiff = val1.xx ^ val2.xx;
    if (!checkIfInRange(xorDiff, numToIndices, lBig, rBig)) { return false; }
    if (diff != xorDiff){ return false; }

    return true;
}

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

        unordered_map<ll, set<int>> numToIndices;
        for(int i = 0; i < n; i++){
            numToIndices[base[i]].insert(i);
        }

        SegTree st(n);

        int ans = 0;
        int q; cin >> q;
        while(q--){
            int type; cin >> type;
            if (type == 1){
                int idx; ll val; cin >> idx >> val; idx--;
                numToIndices[base[idx]].erase(idx);
                numToIndices[val].insert(idx);
                base[idx] = val;
                st.update(idx, val);
            }
            else{
                int l, r; cin >> l >> r; l--; r--;
                if ((r-l+1) % 2 == 0){ continue; }
                if (l == r){ ans++; continue; }
                int mid = (l+r)/2;

                auto val1 = st.query(l, mid);
                auto val2 = st.query(mid+1, r);
                if (checkAlmostEqual(val1, val2, numToIndices, l, mid)){ ans++; continue;}

                val1 = st.query(l, mid-1);
                val2 = st.query(mid, r);
                if (checkAlmostEqual(val2, val1, numToIndices, mid, r)){ ans++; continue; }
            }
        }

        cout << "Case #" << qq << ": " << ans << '\n';
    }
}