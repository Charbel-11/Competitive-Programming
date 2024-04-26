#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//Finds all spf and primes < n in O(n) time
const int SVSZ = 100009; vector<int> primes; int spf[SVSZ];
void buildSieve() {
    vector<int> primes; spf[0] = spf[1] = 1;
    for (int i = 2; i < SVSZ; i++) {
        if (spf[i] == 0) { primes.push_back(i); spf[i] = i; }
        for (int j = 0; j < int(primes.size()) && primes[j] <= spf[i] && i * primes[j] < SVSZ; j++) spf[i * primes[j]] = primes[j];
    }
}

map<int, int> getPrimeFactors(int x){
    map<int, int> m;
    while (x > 1) {
        int d = spf[x], cnt = 0;
        while (x % d == 0) { x /= d; cnt++; }
        m[d] += cnt;
    }
    return m;
}

bool comp(const vector<ll>& seq1, const vector<ll>& seq2){
    vector<ll> fact1 = seq1; fact1.pop_back();
    vector<ll> fact2 = seq2; fact2.pop_back();

    sort(fact1.rbegin(), fact1.rend());
    sort(fact2.rbegin(), fact2.rend());
    while(!fact1.empty() && fact1.back() == 0){ fact1.pop_back(); }
    while(!fact2.empty() && fact2.back() == 0){ fact2.pop_back(); }

    map<int, int> primeFacts1;
    for(auto x : fact1){
        for(int i = 2; i <= x; i++){
            auto curPrimeFact = getPrimeFactors(i);
            for(auto &p : curPrimeFact){ primeFacts1[p.first] += p.second; }
        }
    }
    map<int, int> primeFacts2;
    for(auto x : fact2){
        for(int i = 2; i <= x; i++){
            auto curPrimeFact = getPrimeFactors(i);
            for(auto &p : curPrimeFact){ primeFacts2[p.first] += p.second; }
        }
    }

    for(auto &p : primeFacts1){
        int minRem = min(p.second, primeFacts2[p.first]);
        primeFacts1[p.first] -= minRem; primeFacts2[p.first] -= minRem;
    }

    long long vals1 = 1, vals2 = 1;
    for(auto &p : primeFacts1){
        for(int i = 0; i < p.second; i++){ vals1 *= p.first; }
        assert(vals1 > 0);
    }
    for(auto &p : primeFacts2){
        for(int i = 0; i < p.second; i++){ vals2 *= p.first; }
        assert(vals2 > 0);
    }

    if (vals1 == vals2) return seq1.back() < seq2.back();
    return vals1 < vals2;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, s; cin >> n >> s;
    vector<string> seq(s); for(auto &x : seq){ cin >> x; }

    buildSieve();
    vector<vector<ll>> seqEncoding;
    for(int i = 0; i < s; i++){
        ll numR = 0, numP = 0, numS = 0;
        for(auto c : seq[i]){
            if (c == 'R'){ numR++; }
            else if (c == 'P') { numP++; }
            else { numS++; }
        }
        seqEncoding.push_back({numR, numP, numS, i});
    }

    sort(seqEncoding.begin(), seqEncoding.end(), comp);
    for(auto &v : seqEncoding){
        cout << seq[v.back()] << '\n';
    }
}

