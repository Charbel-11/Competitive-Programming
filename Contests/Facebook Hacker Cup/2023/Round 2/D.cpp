#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
    ll res = 1; x %= mod;
    for (; p; p >>= 1, x = (x * x) % mod)
        if (p & 1) res = (res * x) % mod;
    return res;
}
// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

const int SZ = (int)1e6 + 1;
ll fact[SZ];
void fillFact() {
    fact[0] = 1;
    for (int i = 1; i < SZ; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= mod;
    }
}

ll choose(ll n, ll k) {
    if (k > n) { return 0; }
    ll num = fact[n], denom = fact[k];
    denom *= fact[n - k]; denom %= mod;

    ll multInv = modinv(denom);
    num *= multInv; num %= mod;
    return num;
}

void main_() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ifstream cin("in.txt");
    ofstream cout("out.txt");

    fillFact();

    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        int n, k, d; cin >> n >> k >> d;
        vector<int> H(n); map<int, int> freq;
        for(auto &x : H){ cin >> x; freq[x]++; }

        int maxH = *max_element(H.begin(), H.end());
        vector<ll> dp(maxH + 1, 0);
        for(int i = maxH; i >= 1; i--){
            ll cnt = 0;
            for(int j = i; j <= maxH; j += i){
                cnt += freq[j];
            }
            cnt %= mod;
            dp[i] = choose(cnt, k);
            if (dp[i] > 0) {
                for (int j = 2 * i; j <= maxH; j += i) {
                    dp[i] -= dp[j];
                    dp[i] %= mod;
                }
            }
        }

        ll ans = 0;
        for(int i = 1; i <= maxH; i++){
            if (d % i == 0){
                ans += dp[i];
                ans %= mod;
            }
        }

        ans *= fact[k]; ans %= mod;
        if (ans < 0){ ans += mod; }
        cout << "Case #" << qq << ": " << ans << '\n';
    }
}

static void run_with_stack_size(void (*func)(void), size_t stsize) {
    char *stack, *send;
    stack = (char *)malloc(stsize);
    send = stack + stsize - 16;
    send = (char *)((uintptr_t)send / 16 * 16);
    asm volatile(
            "mov %%rsp, (%0)\n"
            "mov %0, %%rsp\n"
            :
            : "r"(send));
    func();
    asm volatile("mov (%0), %%rsp\n" : : "r"(send));
    free(stack);
}
int main() {
    run_with_stack_size(main_, 1024 * 1024 * 1024); // run with a 1 GiB stack
    return 0;
}