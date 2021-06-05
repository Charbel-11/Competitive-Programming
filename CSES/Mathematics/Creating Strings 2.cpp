#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	if (p == 0) return 1;
	ll w = powe((x*x) % mod, p / 2);
	if (p & 1) w = (w*x) % mod;
	return w;
}

// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }


//With mod; SET SIZE!!
ll fact[(int)1e6 + 2];
void fillFact() {
	fact[0] = 1;
	for (int i = 1; i < 1e6 + 2; i++) {
		fact[i] = fact[i - 1] * i;
		fact[i] %= mod;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	fillFact();

	string s; cin >> s;
	int n = s.size();
	vector<int> freq(26, 0);
	for (auto &c : s) { freq[c - 'a']++; }

	ll ans = fact[n];
	for (int i = 0; i < 26; i++) {
		if (freq[i] == 0) { continue; }
		ans *= modinv(fact[freq[i]]);
		ans %= mod;
	}

	cout << ans << '\n';
}