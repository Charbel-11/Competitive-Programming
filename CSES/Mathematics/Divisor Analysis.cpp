#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	ll res = 1;
	for (; p; p >>= 1, x = (x * x) % mod)
		if (p & 1) res = (res * x) % mod;
	return res;
}

// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<ll> C(n), S(n), P(n);
	ll num = 1;
	for (int i = 0; i < n; i++) {
		ll x, k; cin >> x >> k;
		num *= (k + 1); num %= mod;

		ll prevC = (i ? C[i - 1] : 1);
		C[i] = prevC * (k + 1); C[i] %= (mod - 1);

		ll prevS = (i ? S[i - 1] : 1);
		S[i] = prevS * (powe(x, k + 1) - 1); S[i] %= mod;
		if (S[i] < 0) { S[i] += mod; }
		S[i] *= modinv(x - 1); S[i] %= mod;

		ll prevP = (i ? P[i - 1] : 1);	
		ll power = k * (k + 1) / 2; power %= (mod - 1);
		power *= prevC; power %= (mod - 1);
		P[i] = powe(prevP, k + 1) * powe(x, power); P[i] %= mod;
	}

	cout << num << " " << S[n - 1] << " " << P[n - 1] << '\n';
}
