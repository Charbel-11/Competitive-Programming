#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }

int main() {
	int n; cin >> n;
	vector<ll> a(n); for (auto &x : a) { cin >> x; }

	ll x = a[0];
	for (int i = 1; i < n; i++) {
		x = max(x, a[i]);
	}

	vector<ll> b(n);
	ll swordsTaken = 0;
	ll div = 0;
	for (int i = 0; i < n; i++) {
		b[i] = x - a[i];
		swordsTaken += b[i];
		div = gcd(div, b[i]);
	}

	cout << swordsTaken/div << " " << div << endl;
}