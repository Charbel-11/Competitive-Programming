#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool isPrime(ll n) {
    if (n < 2) { return false; }
    if (n < 4) { return true; }

    for (ll i = 3; i * i <= n; i += 2)
        if (n % i == 0) { return false; }
    return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		ll n; cin >> n;
        ll d = 1, smallestP = n;
        while(d * d <= n){
            if (n % d == 0) {
                if (isPrime(d)) {
                    smallestP = d;
                    break;
                }
                if (isPrime(n/d)){
                    smallestP = min(smallestP, n/d);
                }
            }
            d++;
        }

        cout << n/smallestP << " " << n/smallestP*(smallestP-1) << '\n';
	}
}