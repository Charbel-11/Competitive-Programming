#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) { return (b ? gcd(b, a % b) : a); }
ll digitSum(ll n) {
	ll ans = 0;
	while (n) {
		ans += n % 10; n /= 10;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		ll n; cin >> n;
		while (gcd(n, digitSum(n)) == 1) { n++; }
		cout << n << '\n';
	}
}
