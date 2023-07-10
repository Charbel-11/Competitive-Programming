#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

vector<ll> prob;

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

struct edge {
    int u, v; edge() {}
    edge(int _u, int _v) :
            u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
    vector<node> nodes;
    vector<ll> sum;
    vector<int> par;
    int root, n;

    tree(int _n, int _r = 0) : n(_n), root(_r) {
        nodes.resize(n); sum.resize(n, 0);
        par.resize(n, -1);
    }

    void add_edge(int u, int v) {
        edge e1(u, v), e2(v, u);
        nodes[u].edges.push_back(e1);
        nodes[v].edges.push_back(e2);
    }

    void dfs(int u, int p){
        par[u] = p; sum[u] = prob[u];
        for(auto &e : nodes[u].edges) {
            if (e.v == p) { continue; }
            dfs(e.v, u);
            sum[u] += sum[e.v];
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, k; cin >> n >> k;
    prob.resize(n, 0);
    for(int i = 0; i < k; i++){
        int cur; cin >> cur; cur--;
        prob[cur] = 1;
    }

    tree t(n);
    vector<pair<int, int>> edges;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        t.add_edge(u, v);
        edges.emplace_back(u, v);
    }

    t.dfs(0, -1);
    ll ans = 0, inv2 = modinv(2);

    for(auto& [u,v] : edges){
        if (t.par[u] == v){ swap(u, v); }

        ll puv = prob[u]*(1-prob[v]); puv %= mod;
        puv *= inv2; puv %= mod;
        ll pvu = prob[v]*(1-prob[u]); pvu %= mod;
        pvu *= inv2; pvu %= mod;

        ll sum1 = t.sum[v] * (k-t.sum[v]); sum1 %= mod;
        ll sum2 = (t.sum[v] + 1) * (k - t.sum[v] - 1); sum2 %= mod;
        ll sum3 = (t.sum[v] - 1) * (k - t.sum[v] + 1); sum3 %= mod;

        ll val1 = (1 - puv - pvu) * sum1; val1 %= mod;
        ll val2 = puv * sum2; val2 %= mod;
        ll val3 = pvu * sum3; val3 %= mod;

        ans += val1 + val2 + val3; ans %= mod;

        ll newVal = (prob[u]+prob[v]) * inv2;
        newVal %= mod;
        prob[u] = prob[v] = newVal;
    }

    ll tmp = k*(k-1)/2; tmp %= mod;
    ans *= modinv(tmp);  ans %= mod;
    if (ans < 0){ ans += mod ;}
    cout << ans << '\n';
}