#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

int n;

ll solve1DProblem(const vector<ll>& A, const vector<ll>& x){
    ll ans = 0;

    ll sumSquares = 0, sum = 0;
    for(int i = 0; i < n; i++){
        sum += A[i]; sum %= mod;
        ll cur2 = (A[i] * A[i]) % mod;
        sumSquares += cur2; sumSquares %= mod;
    }

    for(int i = 0; i < x.size(); i++){
        ll temp = -2 * sum * x[i]; temp %= mod;
        if (temp < 0){ temp += mod; }

        ll nX2 = x[i] * x[i]; nX2 %= mod;
        nX2 *= n; nX2 %= mod;

        ll cur = nX2 + sumSquares; cur %= mod;
        cur += temp; cur %= mod;

        ans += cur; ans %= mod;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ifstream cin("in.txt");
    ofstream cout("out.txt");

    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cin >> n;
        vector<ll> A(n), B(n);
        for(int i = 0; i < n; i++){
            cin >> A[i] >> B[i];
        }

        int q; cin >> q;
        vector<ll> x(q), y(q);
        for(int i = 0; i < q; i++){
            cin >> x[i] >> y[i];
        }

        ll ans = solve1DProblem(A, x);
        ans += solve1DProblem(B, y);
        ans %= mod;

        cout << "Case #" << qq << ": " << ans << '\n';
    }
}