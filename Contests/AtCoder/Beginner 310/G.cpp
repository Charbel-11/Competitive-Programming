#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
    ll res = 1; x %= mod;
    for (; p; p >>= 1, x = (x * x) % mod) {
        if (p & 1) { res = (res * x) % mod; }
    }
    return res;
}
// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

int main(){
    int N; ll K; cin >> N >> K;
    vector<int> A(N); for(auto &x : A) { cin >> x; x--; }
    vector<ll> B(N); for(auto &x : B){ cin >> x; }

    auto applyAtoB = [&]{
        vector<ll> newB(N, 0);
        for (int i = 0; i < N; i++){
          newB[A[i]] += B[i];
          newB[A[i]] %= mod;
        }
        B = newB;
    };

    ll mInv = modinv(K);

    applyAtoB();
    vector<ll> ans(N, 0);
    while(K){
        if (K & 1){
            for(int i = 0; i < N; i++){ ans[i] += B[i]; ans[i] %= mod; }
            applyAtoB();
        }

        vector<ll> curB = B;
        applyAtoB();
        for(int i = 0; i < N; i++){ B[i] += curB[i]; B[i] %= mod; }

        vector<int> newA = A;
        for(int i = 0; i < N; i++){ newA[i] = A[A[i]]; }
        A = newA;

        K /= 2;
    }

    for(auto &x : ans){
        cout << (x * mInv) % mod << ' ';
    }
    cout << '\n';
}