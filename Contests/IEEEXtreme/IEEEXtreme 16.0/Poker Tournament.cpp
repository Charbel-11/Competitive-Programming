#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const ll INF = 1e17;	//Change if needed
const int MAXK = 52;

vector<ll> base;
ll fact[MAXK];

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

enum Type { MAX, SET };

struct StVal {
    vector<ll> sumsA;    //sums[i] = sums of elements to the power i
    ll min1 = INF, min2 = INF;
    ll lazySet = INF;
    int freqMin = 0;
    StVal() { sumsA.resize(MAXK); }
    StVal(const ll _v) {
        min1 = _v;
        freqMin = 1;
        min2 = INF;

        sumsA.resize(MAXK); sumsA[0] = 1;
        for(int k = 1; k < MAXK; k++){
            sumsA[k] = (sumsA[k-1] * _v) % mod;
        }
    }
    StVal(const StVal& v1, const StVal& v2) {
        if (sumsA.size() < MAXK){ sumsA.resize(MAXK); }
        for(int k = 0; k < MAXK; k++){
            sumsA[k] = (v1.sumsA[k] + v2.sumsA[k]) % mod;
        }

        if (v1.min1 < v2.min1) {
            min1 = v1.min1; freqMin = v1.freqMin;
            min2 = min(v1.min2, v2.min1);
        }
        else if (v1.min1 > v2.min1) {
            min1 = v2.min1; freqMin = v2.freqMin;
            min2 = min(v2.min2, v1.min1);
        }
        else {
            min1 = v1.min1; freqMin = v1.freqMin + v2.freqMin;
            min2 = min(v1.min2, v2.min2);
        }
        //lazySet = INF;
    }

    //Applies changes of type at node si using val
    void updateVal(const ll val, const Type type, const int lo, const int hi) {
        ll len = hi - lo + 1;
        if (type == MAX) {
            ll valFactor = 1, minFactor = 1;
            for(int k = 0; k < MAXK; k++){
                sumsA[k] += ((valFactor - minFactor) * freqMin) % mod;
                if (sumsA[k] < 0){ sumsA[k] += mod; }
                valFactor = (valFactor * val) % mod;
                minFactor = (minFactor * min1) % mod;
            }

            min1 = val;
            if (lazySet != INF) { lazySet = max(lazySet, val); }
        }
        else if (type == SET) {
            min1 = val; min2 = INF; freqMin = len;
            lazySet = val;

            ll valFactor = 1;
            for(int k = 0; k < MAXK; k++){
                sumsA[k] = (valFactor * len) % mod;
                valFactor = (valFactor * val) % mod;
            }
        }
    }
};

struct SegTree {
    int n;
    vector<StVal> st;
    vector<int> leaves;

    SegTree(const int n) : n(n) {
        leaves.resize(n);
        init(1, 0, n - 1);
    }

    StVal query(const int l, const int r) { return (l <= r && l < n&& r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }

    // Set each element A[i] in [l, r] to be max(A[i], x)
    void updateMax(const int l, const int r, const ll maxV) { if (l <= r) rangeUpdate(l, r, maxV, 1, 0, n - 1, MAX); }
    // Set each element A[i] in [l, r] to be x
    void updateSet(const int l, const int r, const ll x) { if (l <= r) rangeUpdate(l, r, x, 1, 0, n - 1, SET); }

private:
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

    //si has correct values and already used lazy values which it will propagate
    void propagateLazy(const int si, const int lo, const int hi) {
        if (lo == hi) { st[si].lazySet = INF; return; }
        const int mid = (lo + hi) >> 1;
        //Set
        if (st[si].lazySet != INF) {
            st[si << 1].updateVal(st[si].lazySet, SET, lo, mid);
            st[si << 1 | 1].updateVal(st[si].lazySet, SET, mid + 1, hi);
            st[si].lazySet = INF;
            return;
        }
        //Max
        if (st[si].min1 > st[si << 1].min1) {
            st[si << 1].updateVal(st[si].min1, MAX, lo, mid);
        }
        if (st[si].min1 > st[si << 1 | 1].min1) {
            st[si << 1 | 1].updateVal(st[si].min1, MAX, mid + 1, hi);
        }
    }

    StVal query(const int l, const int r, const int si, const int lo, const int hi) {
        if (l <= lo && hi <= r) { return st[si]; }

        propagateLazy(si, lo, hi);
        const int mid = (lo + hi) >> 1;
        if (r <= mid) return query(l, r, si << 1, lo, mid);
        if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
        return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
    }

    //True if the operation will not be applied to any element in the range
    bool orCheck(const int si, const ll val, const Type type) {
        if (type == MAX) { return st[si].min1 >= val; }
        else { return false; }
    }
    //True if we can set a lazy value on that range (for min/max, it means the operation is done for the max/min only)
    bool andCheck(const int si, const ll val, Type type) {
        if (type == MAX) { return st[si].min2 >= val; }
        else { return true; }
    }

    void rangeUpdate(const int l, const int r, const ll val, const int si, const int lo, const int hi, const Type type) {
        if (hi < l || r < lo || orCheck(si, val, type)) { return; }
        if (l <= lo && hi <= r && andCheck(si, val, type)) {
            st[si].updateVal(val, type, lo, hi);
        }
        else {
            propagateLazy(si, lo, hi);
            const int mid = (lo + hi) >> 1;
            rangeUpdate(l, r, val, si << 1, lo, mid, type);
            rangeUpdate(l, r, val, si << 1 | 1, mid + 1, hi, type);
            st[si] = StVal(st[si << 1], st[si << 1 | 1]);
        }
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    fact[0] = 1;
    for(ll i = 1; i < MAXK; i++){
        fact[i] = (fact[i-1] * i) % mod;
    }

    int n, q; cin >> n >> q;
    base.resize(n); for(auto &x : base){ cin >> x; }

    SegTree st(n);
    while(q--){
        int type; cin >> type;
        int l, r; cin >> l >> r;
        if (type == 0){
            ll c; cin >> c;
            st.updateSet(l, r, c);
        }
        else if (type == 1){
            ll c; cin >> c;
            st.updateMax(l, r, c);
        }
        else{
            int K; cin >> K;

            if (K > (r - l + 1)) { cout << 0 << '\n'; continue; }

            auto res = st.query(l, r);
            auto sumsA = res.sumsA;
            vector<ll> sumsK(K+1, 0);
            sumsK[1] = sumsA[1]; sumsK[0] = 1;
            for(int k = 2; k <= K; k++){
                ll sign = 1, aF = 1;
                for(int j = 1; j <= k; j++){
                    ll cur = (sumsA[j] * sumsK[k-j]) % mod;
                    cur *= aF; cur %= mod;
                    sumsK[k] = (sumsK[k] + sign * cur) % mod;
                    if (sumsK[k] < 0){ sumsK[k] += mod; }
                    sign *= -1;
                    aF *= (k-j); aF %= mod;
                }
            }

            ll ans = (sumsK[K] * modinv(fact[K])) % mod;
            cout << ans << '\n';
        }
    }
}