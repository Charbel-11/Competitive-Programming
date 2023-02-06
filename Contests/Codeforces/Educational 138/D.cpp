#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

const int SVSZ = 300009;
int spf[SVSZ]; //Smallest Prime Factor
vector<int> primes;

void buildSieve() {
    spf[0] = spf[1] = 1;
    for (int i = 2; i < SVSZ; i++) {
        if (spf[i] == 0) { primes.push_back(i);	spf[i] = i; }
        for (int j = 0; j < int(primes.size()) && primes[j] <= spf[i] && i * primes[j] < SVSZ; j++)
            spf[i * primes[j]] = primes[j];
    }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    buildSieve();
	int n; ll m; cin >> n >> m;
    ll cur = m; m %= mod;

    ll ans = 0, powM = 1;
    for(int i = 1; i <= n; i++){
        powM *= m; powM %= mod;
        ans += powM; ans %= mod;
    }

    int j = 0; ll numChoices = 1;
    for(int i = 1; i <= n; i++){
        if (primes[j] == i) {
            cur /= i;
            j++;
        }
        numChoices *= (cur%mod); numChoices %= mod;
        ans -= numChoices; ans %= mod;
    }

    if (ans < 0){ ans += mod; }
    cout << ans << '\n';
}