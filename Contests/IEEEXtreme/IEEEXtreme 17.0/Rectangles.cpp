#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//Finds {prime, multiplicity} in O(sqrt(x))
vector<pair<ll, int>> getPrimeFactorsSlow(ll x) {
    vector<pair<ll, int>> ans; ll num = 2;
    while (x != 1 && num*num <= x) {
        if (x % num == 0) {
            int k = 0;
            while (x % num == 0) { x /= num; k++; }
            ans.push_back({ num,k });
        }
        num++;
    }
    if (x != 1) { ans.push_back({ x,1 }); }
    return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int p, q; cin >> p >> q;
    map<int, int> freqPrimes;
    for(int i = p; i <= q; i++){
        auto primes = getPrimeFactorsSlow(i);
        for(auto &p : primes){
            if (p.first < 100) { freqPrimes[p.first]++; }
        }
    }

    vector<int> relevantPrimes;
    for(auto &p : freqPrimes){
        if (p.second >= 2){ relevantPrimes.push_back(p.first); }
    }
    int numPrimes = relevantPrimes.size();
    assert(numPrimes <= 23);

    sort(relevantPrimes.begin(), relevantPrimes.end());
    vector<pair<ll, int>> valToMask;
    for(int i = p; i <= q; i++){
        int curMask = 0;
        for(int j = 0; j < relevantPrimes.size(); j++){
            if (i % relevantPrimes[j] == 0){
                curMask |= (1<<j);
            }
        }
        valToMask.emplace_back(i, curMask);
    }

    vector<ll> dp((1<<numPrimes), -1e9); dp[0] = 0;
    for(int i = 0; i <= q-p; i++){
        for(int j = (1<<numPrimes) - 1; j >= 0; j--){
            auto [val, curMask] = valToMask[i];
            if ((j | curMask) > j){ continue; }
            if (dp[j ^ curMask] < 0){ continue; }
            dp[j] = max(dp[j], dp[j ^ curMask] + val);
        }
    }

    ll ans = *max_element(dp.begin(), dp.end());
    cout << ans << '\n';
}

