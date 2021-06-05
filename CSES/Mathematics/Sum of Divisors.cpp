#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    int ans = 0;
    for (ll i = 1, j; i <= n; i = j) {
        ll q = n / i; j = n / q + 1;    //e.g., 10/4=2 and 10/2=5; where 10/4=10/5=2
        // process terms [i..j-1] of the summation
        // since they all have the same quotient q
        // now we add q*sum(i..j-1) to the answer
        ll x = j - i, y = i + j - 1; // x*y/2 = sum(i..j-1)= j*(j-1)-i*(i-1)=j^2-i^2-j+i
        if (x % 2 == 0) { x /= 2; }
        else { y /= 2; }
        x %= mod, y %= mod;
        ans = (ans + q % mod * x % mod * y % mod) % mod;
    }
	cout << ans << '\n';
}