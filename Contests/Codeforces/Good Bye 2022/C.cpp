#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int SVSZ = 100;
int spf[SVSZ]; //Smallest Prime Factor
vector<ll> primes;

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

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        vector<ll> a(n); for(auto &x : a){ cin >> x; }

        bool exists = true;

        set<ll> seen;
        for(auto &x : a){
            if (seen.count(x)){ exists = false; break; }
            seen.insert(x);
        }

        for (ll p : primes){
            if (p > (n+1)/2){ break; }
            vector<int> freq(p, 0);
            for(auto &x : a){
                freq[x%p]++;
            }

            bool OK = false;
            for(int i = 0; i < p; i++){
                if (freq[i] <= 1){ OK = true; }
            }
            if (!OK){ exists = false; break; }
        }

        cout << (exists ? "YES" : "NO") << '\n';
	}
}