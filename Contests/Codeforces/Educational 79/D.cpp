#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

const long long mod = 998244353;
typedef long long ll;

ll egcd(ll a, ll b, ll &x, ll &y) { 
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	} 
	ll d = egcd(b, a%b, y, x);
	y = a - x * (a / b) - y;
	x = b - x;
	return d;
}

ll inverse(ll a, ll p) {
	ll x, y;
	egcd(a%p + p, p, x, y);
	return x % p;
}

long long gcd(long long a, long long b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a%b);
}
long long lcm(ll a, ll b) { return (long long)(a / gcd(a, b)) * b; }


void normalize(pair<long long, long long>& p) {
	if (p.first == 0) {
		p.second = 1ll;
	}

	p.first %= mod; p.second %= mod;
	long long g = gcd(p.first, p.second);
	p.first /= g;
	p.second /= g;
}

int main() {
	long long n; cin >> n;
	vector<long long> k(n);
	vector<vector<long long>> a(n);

	map<long long, long long> m;
	for (int i = 0; i < n; i++) {
		cin >> k[i];

		for (int j = 0; j < k[i]; j++) {
			long long temp; cin >> temp;
			a[i].push_back(temp);
			m[temp]++;
		}
	}

	pair<long long, long long> sumP = { 0,1 };

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k[i]; j++) {
			pair<long long, long long> inter = { m[a[i][j]], k[i] };
			normalize(inter);
			pair<long long, long long> multP = { inter.first, inter.second * n };
			normalize(multP);

			ll den = lcm(sumP.second, multP.second);
			sumP = { sumP.first*(den/sumP.second) + multP.first*(den/multP.second), den };
			normalize(sumP);
		}
	}
	pair<long long, long long> p = { sumP.first, n * sumP.second };
	normalize(p);

	long long res = p.first % mod;
	long long temp = inverse(p.second, mod);
	long long f = (res*temp) % mod; 
	while (f < 0) { f += mod; f %= mod; }
	cout << f << endl;
}