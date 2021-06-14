#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;
vector<int> primes;

void simpleSieve(int limit, vector<int>& prime) {
    vector<bool> mark(limit + 1, true);
    for (int p = 2; p * p < limit; p++) {
        if (mark[p] == true) {
            for (int i = p * p; i < limit; i += p)
                mark[i] = false;
        }
    }

    for (int p = 2; p < limit; p++) {
        if (mark[p] == true) { primes.push_back(p); prime.push_back(p); }
    }
}

void segmentedSieve(int n) {
    int limit = floor(sqrt(n)) + 1;
    vector<int> prime; prime.reserve(limit);
    simpleSieve(limit, prime);

    int low = limit;
    int high = 2 * limit;

    while (low < n) {
        if (high >= n) high = n;

        vector<bool> mark(limit + 1, true);

        for (int i = 0; i < prime.size(); i++) {
            int loLim = floor(low / prime[i]) * prime[i];
            if (loLim < low)
                loLim += prime[i];

            for (int j = loLim; j < high; j += prime[i])
                mark[j - low] = false;
        }

        // Numbers which are not marked as false are prime
        for (int i = low; i < high; i++)
            if (mark[i - low] == true)
                primes.push_back(i);

        // Update low and high for next segment
        low = low + limit;
        high = high + limit;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    segmentedSieve(1e9 + 50);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        ll Z; cin >> Z;
        ll ans = 0;

        int l = 0, r = primes.size() - 2;
        while (l <= r) {
            int mid = l + ((r - l) >> 1);
            ll cur = (ll)primes[mid] * (ll)primes[mid + 1];
            if (cur > Z) { r = mid - 1; }
            else { ans = max(ans, cur); l = mid + 1; }
        }

        cout << "Case #" << qq << ": " << ans << '\n';
    }
}
